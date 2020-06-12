#! /usr/bin/env bash
#***************************************************************************#
# Ubuntu-only                                                               #
# Usage:                                                                    #
# Step 1:                                                                   #
#   bash setup_ssh_tunnel.sh                                                #
# Step 2:                                                                   #
#   ssh -p <remote-ssh-server-port> <username>@<ssh-server-addr>            #
#       Eg. ssh -p 22 panda@myexample.com                                   #
# Step 3: On ssh-server side                                                #
#   ssh localhost -p <reverse-port>                                         #
#       Eg. ssh localhost -p 19527                                          #
#***************************************************************************#
CURRENT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"

: ${SERVER_ADDR:="example.com"}
: ${SERVER_TAG:="${SERVER_ADDR%%.*}"}
: ${SERVER_PORT:=22}
: ${SERVER_USER:="your_server_username"}
: ${SERVER_PASS:="your_server_password"}

: ${REVERSE_PORT:=9527}
: ${LOCAL_PORT:=22}

IFS='' read -r -d '' SECURE_TUNNEL_CONFIG_TEXT << EOF
TARGET=${SERVER_ADDR}
LOCAL_ADDR=0.0.0.0
REVERSE_PORT=${REVERSE_PORT}
REMOTE_USER=${SERVER_USER}
REMOTE_PORT=${SERVER_PORT}
LOCAL_PORT=${LOCAL_PORT}
KEY_FILE=$HOME/.ssh/id_rsa
EOF

SERVER_SIDE_CONFIG="/etc/ssh/ssh_config"
CLIENT_SIDE_CONFIG="/etc/ssh/sshd_config"

PRIV_AUTH="$HOME/.ssh/id_rsa"
PUB_AUTH="${PRIV_AUTH}.pub"

set -o errexit

function prereq_software_install() {
    if ! dpkg -s openssh-server &>/dev/null \
       ! dpkg -s openssh-client &>/dev/null ; then
        sudo apt-get -y update && \
        sudo apt-get -y install openssh-server openssh-client
    fi
}

IFS='' read -r -d '' EXPECT_SCRIPT_TEXT << EOF
spawn ssh-copy-id -i ${PUB_AUTH} -p ${SERVER_PORT} ${SERVER_USER}@${SERVER_ADDR}
expect "password"
send "${SERVER_PASS}\r"
interact
EOF

function ssh_keygen_install() {
    if [[ ! -f "${PUB_AUTH}" || ! -f "${PRIV_AUTH}" ]]; then
        ssh-keygen -t rsa -b 2048 -N "" -f "${PRIV_AUTH}" -q
    fi
    # ssh-copy-id -i "${PUB_AUTH}" -p "${SERVER_PORT}" "${SERVER_USER}@${SERVER_ADDR}"
    # Ref: https://stackoverflow.com/questions/41165719/embedding-an-expect-inside-a-bash-script
    expect -c "${EXPECT_SCRIPT_TEXT//
/;}"
}

function ssh_server_config() {
    if grep -q ServerAliveInterval "${SERVER_SIDE_CONFIG}"; then
        return
    fi
    local TAB="    "
    sudo chmod 0644  "${SERVER_SIDE_CONFIG}"
    echo "${TAB}ServerAliveInterval 30" | sudo tee -a "${SERVER_SIDE_CONFIG}"
    echo "${TAB}ServerAliveCountMax 4"  | sudo tee -a "${SERVER_SIDE_CONFIG}"
}

function sshd_client_config() {
    if grep -q ClientAliveInterval "${CLIENT_SIDE_CONFIG}"; then
        return
    fi
    sudo chmod 0644 "${CLIENT_SIDE_CONFIG}"
    echo "ClientAliveInterval 30" | sudo tee -a "${CLIENT_SIDE_CONFIG}"
    echo "ClientAliveCountMax 4"  | sudo tee -a "${CLIENT_SIDE_CONFIG}"
}

function test_usage_hint() {
    local REV_CMD="ssh -i ${PRIV_AUTH} -p ${SERVER_PORT} \
-N -R ${REVERSE_PORT}:localhost:${LOCAL_PORT} \
${SERVER_USER}@${SERVER_ADDR}"
    echo "#******************************************************************#"
    echo "# You can run the following command to test ssh-reverse-tunnel:     "
    echo "#     ${REV_CMD} "
    echo "#*******************************************************************#"
}

function systemd_config_install() {
    local systemd_config_path="/etc/default/secure-tunnel@${SERVER_TAG}"
    echo "$SECURE_TUNNEL_CONFIG_TEXT" | sudo tee "${systemd_config_path}"
    sudo cp -f "${CURRENT_DIR}/secure-tunnel-service.sample" /etc/systemd/system/secure-tunnel@.service
}

function start_systemd_keepalive() {
    local service_name="secure-tunnel@${SERVER_TAG}.service"
    sudo systemctl daemon-reload
    # Start secure-tunnel on boot
    sudo systemctl enable "${service_name}"
    sudo systemctl start "${service_name}"
    sudo systemctl status "${service_name}"
}

function main() {
    echo "Make sure openssh-server/client is installed..."
    prereq_software_install
    echo "Generate and copy ${PUB_AUTH} to ${SERVER_USER}@${SERVER_ADDR} ..."
    ssh_keygen_install
    echo "Make sure ${SERVER_SIDE_CONFIG} adjusted ..."
    ssh_server_config
    echo "Make sure ${CLIENT_SIDE_CONFIG} adjusted ..."
    sshd_client_config
    test_usage_hint
    systemd_config_install
    start_systemd_keepalive
    echo "Done secure-tunnel-setup-and-keepalive-using-systemd-on-boot!"
}

main "$@"
