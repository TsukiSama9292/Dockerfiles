# [TsukiSama9292/Dockerfiles 存放各類 Dockerfile](https://github.com/TsukiSama9292/Dockerfiles)

<div align="center">
  <p>  
    <a href="https://github.com/TsukiSama9292/Dockerfiles/blob/main/LICENSE"><img src="https://img.shields.io/badge/License-Apache%202.0-blue.svg" alt="MIT License" /></a>
    <a href="https://deepwiki.com/TsukiSama9292/Dockerfiles"><img src="https://deepwiki.com/badge.svg" alt="Ask DeepWiki" /></a>
  </p>
</div>

## 儲存庫功能
1. 每日定時更新鏡像，保持鏡像最新版本，減少資安漏洞。
2. 公開化且透明化發開技術和開發技巧，所有人皆可根據`Apache 2.0`協議，任意使用、複製、修改本儲存庫。

## 儲存庫檔案結構

### .github/workflows
放置 Github Actions 所有的執行檔(.yml)，所有執行檔皆在台灣時間00:00(GMT+8)執行。

### kasm_workspace
放置 Kasm Workspace 相關的 VNC dockerfile，便於開發者在 Kasm Workspace 保持開箱即用的環境，鏡像中已安裝常見的開發工具。

| 鏡像 | 功能 | 維護狀態 |
|:---:|:---:|:---:|
| <img src="https://img.shields.io/badge/Docker-ubuntu--jammy-blue?style=flat-square&logo=docker&logoColor=white" alt="Ubuntu Jammy badge"><br>[ubuntu‑jammy‑dind](https://hub.docker.com/r/tsukisama9292/ubuntu-jammy-dind) | <img src="https://assets.ubuntu.com/v1/29985a98-ubuntu-logo32.png" alt="Ubuntu logo" width="20"> 適用於開發全端伺服器 | 🟢 積極 |
| <img src="https://img.shields.io/badge/Docker-steam-black?style=flat-square&logo=steam&logoColor=white" alt="Steam badge"><br>[steam](https://hub.docker.com/r/tsukisama9292/steam) | <img src="https://cdn.jsdelivr.net/gh/simple-icons/simple-icons/icons/steam.svg" alt="Steam logo" width="20"> 適用於遊戲玩家 | 🟢 積極 |

### online_judge
放置 k12edu 團隊的程式解題網站的 dockerfile，方面管理。

### src
來源於[kasmtech/workspaces-images](https://github.com/kasmtech/workspaces-images)的腳本資料夾(複製時間: 2025-06-21)，哈希值: 062a0bff63b6e3953f4540c8f0d6289c44493d24  
內部的腳本用於建制 Kasm VNC 相關鏡像。  