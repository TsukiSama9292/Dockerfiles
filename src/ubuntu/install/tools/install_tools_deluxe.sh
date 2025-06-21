#!/usr/bin/env bash
set -ex

apt-get update
apt-get install -y vlc git tmux

# Add install gnome-keyring tree (edit from: TsukiSama9292)
apt-get install -y gnome-keyring tree