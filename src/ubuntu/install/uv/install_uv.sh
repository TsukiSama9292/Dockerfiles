#!/bin/bash
set -e
set -x

# Install uv(edit from: TsukiSama9292)
curl -LsSf https://astral.sh/uv/install.sh | env UV_INSTALL_DIR="/usr/local/bin" INSTALLER_NO_MODIFY_PATH=1 sh