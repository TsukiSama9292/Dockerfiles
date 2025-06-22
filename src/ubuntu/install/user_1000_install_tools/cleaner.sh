#!/bin/bash

sudo apt-get autoremove -y
sudo apt-get autoclean -y

# File cleanups
sudo rm -Rf \
  /home/kasm-default-profile/.cache \
  /home/kasm-user/.cache \
  /tmp \
  /var/lib/apt/lists/* \
  /var/tmp/*
sudo mkdir -m 1777 /tmp