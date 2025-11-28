#!/usr/bin/env bash
set -ex

# nvm 系統安裝目錄
export NVM_DIR="/usr/local/nvm"

echo "[1/6] 建立 NVM 目錄..."
mkdir -p "$NVM_DIR"
chown -R $(whoami):$(whoami) "$NVM_DIR"

echo "[2/6] 安裝 nvm..."
# INSTALLER_NO_MODIFY_PATH=1 可避免修改使用者的 .bashrc
env NVM_DIR="$NVM_DIR" INSTALLER_NO_MODIFY_PATH=1 bash -c \
  "curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.3/install.sh | bash"

echo "[3/6] 載入 nvm..."
# Source nvm.sh （此時已經裝在 NVM_DIR 下）
if [ -s "$NVM_DIR/nvm.sh" ]; then
    . "$NVM_DIR/nvm.sh"
else
    echo "錯誤：找不到 nvm.sh"
    exit 1
fi

echo "[4/6] 安裝 Node.js LTS (22) 並設定為 default..."
nvm install 22
nvm alias default 22

echo "[5/6] 加入全系統自動載入..."
tee /etc/profile.d/nvm.sh >/dev/null <<EOF
export NVM_DIR=/usr/local/nvm
[ -s "\$NVM_DIR/nvm.sh" ] && \. "\$NVM_DIR/nvm.sh"
EOF

# 互動 shell 也要載入（例如 bash -i）
tee -a /etc/bash.bashrc >/dev/null <<EOF
[ -s "/etc/profile.d/nvm.sh" ] && \. "/etc/profile.d/nvm.sh"
EOF

echo "[6/6] （可選）加入 Node 目前版本到 PATH..."
NODE_VERSION=$(ls $NVM_DIR/versions/node/)
# 注意：版本取決於 nvm install 時實際取得的 node 版本
echo "export PATH=$NVM_DIR/versions/node/$NODE_VERSION/bin:\$PATH" | tee /etc/profile.d/node_path.sh >/dev/null

echo "=== 完成！==="
echo "重新登入或 new shell 後可使用 nvm/node"
