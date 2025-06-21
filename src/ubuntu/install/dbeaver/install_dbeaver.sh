#!/bin/bash
set -e
set -x

wget https://dbeaver.io/files/dbeaver-ce_latest_amd64.deb
dpkg -i dbeaver-ce_latest_amd64.deb
apt update
apt-get install -f -y
rm -rf dbeaver-ce_latest_amd64.deb