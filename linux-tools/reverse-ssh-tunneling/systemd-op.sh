#! /usr/bin/env bash

: ${SERVER_TAG:=storypku}

SERVICE_NAME="secure-tunnel@${SERVER_TAG}.service"

sudo systemctl daemon-reload
sudo systemctl enable ${SERVICE_NAME}
sudo systemctl start ${SERVICE_NAME}
sudo systemctl status ${SERVICE_NAME}
