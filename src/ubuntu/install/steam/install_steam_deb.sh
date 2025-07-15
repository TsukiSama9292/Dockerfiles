#!/usr/bin/env bash
set -ex

# Install Steam by downloading the .deb package
dpkg --add-architecture i386
apt-get update
curl -sSL https://steamcdn-a.akamaihd.net/client/installer/steam.deb -o /tmp/steam.deb
dpkg -i /tmp/steam.deb || apt-get install -f -y
rm -f /tmp/steam.deb