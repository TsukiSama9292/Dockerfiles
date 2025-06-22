#!/bin/bash

sudo apt-get remove --purge gnome-keyring -y
sudo apt-get update
sudo apt-get install -y gnome-keyring tree