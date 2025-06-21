#!/bin/bash
set -e
set -x

curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.2/install.sh | bash
echo "source \$HOME/.nvm/nvm.sh" >> ~/.bashrc
export NVM_DIR="$HOME/.nvm" && \
[ -s "$NVM_DIR/nvm.sh" ] && \. "$NVM_DIR/nvm.sh" && \
nvm install node && \
nvm install 22 && \
nvm alias default 22