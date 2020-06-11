# Reverse SSH Tunneling Kept Alive with Systemd

## PreReq

Linux system with systemd enabled

## How to Run

#### Step 1: Setup SSH Tunneling on Your Host

```
bash setup_ssh_tunnel.sh
```

#### Step 2: SSH Tunneling Keepalive using Systemd

```
sudo cp secure-tunnel-service.sample /etc/systemd/system/secure-tunnel@.service
cp secure-tunnel-panda.conf.sample secure-tunnel@panda
# After secure-tunnel@panda modified:
sudo mv secure-tunnel@panda /etc/default/secure-tunnel@panda
```

#### Step 3: Start `secure-tunnel` Systemd Service

```
sudo systemctl daemon-reload
sudo systemctl start secure-tunnel@panda.service
sudo systemctl status secure-tunnel@panda.service
```

If you want to start `secure-tunnel` service on boot, run:

```
sudo systemctl enable secure-tunnel@panda.service
```

