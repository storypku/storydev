#! /usr/bin/env bash
#***************************************************************************#
# Ubuntu-only                                                               #
# Usage:                                                                    #
# Step 1:                                                                   #
#   bash setup_ssh_tunnel.sh                                              #
# Step 2:                                                                   #
#   ssh -p <remote-ssh-server-port> <username>@<ssh-server-addr>            #
#       Eg. ssh -p 4522 story@storypku.com                                  #
# Step 3: On ssh-server side                                                #
#   ssh localhost -p <reverse-port>                                         #
#       Eg. ssh localhost -p 19527                                          #
#***************************************************************************#
set -o errexit

: ${SERVER_ADDR:="example.com"}
: ${SERVER_PORT:=22}
: ${SERVER_USER:="story"}
: ${SERVER_PASS:="Secret"}

: ${REVERSE_PORT:=19527}
: ${LOCAL_PORT:=22}

SERVER_SIDE_CONFIG="/etc/ssh/ssh_config"
CLIENT_SIDE_CONFIG="/etc/ssh/sshd_config"

PRIV_AUTH="$HOME/.ssh/id_rsa"
PUB_AUTH="${PRIV_AUTH}.pub"

function prereq_software_install() {
    if [ ! dpkg -s openssh-server &>/dev/null ] \
       [ ! dpkg -s openssh-client &>/dev/null ]; then
        sudo apt-get -y update && \
        sudo apt-get -y install openssh-server openssh-client
    fi
}

function ssh_keygen_install() {
    if [[ ! -f "${PUB_AUTH}" || ! -f "${PRIV_AUTH}" ]]; then
        ssh-keygen -t rsa -b 2048 -N "" -f "${PRIV_AUTH}" -q
    fi
    # TODO: expect
    ssh-copy-id -i "${PUB_AUTH}" -p "${SERVER_PORT}" "${SERVER_USER}@${SERVER_ADDR}"
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

function final_usage_hint() {
    local REV_CMD="ssh -i ${PRIV_AUTH} -p ${SERVER_PORT} \
-N -R ${REVERSE_PORT}:localhost:${LOCAL_PORT} \
${SERVER_USER}@${SERVER_ADDR}"
    echo "#******************************************************************#"
    echo "# Please run the following command to start ssh-reverse-tunnel:    "
    echo "#     ${REV_CMD} "
    echo "#*******************************************************************#"
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
    final_usage_hint
}

main "$@"
