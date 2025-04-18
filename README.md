# TsukiSama9292/Dockerfiles 存放各類 Dockerfile

## 儲存庫功能
1. 每日定時更新鏡像，保持鏡像最新版本，減少資安漏洞。
2. 公開化且透明化發開技術和開發技巧，所有人皆可根據`Apache 2.0`協議，任意使用、複製、修改本儲存庫。

## 儲存庫檔案結構

### .github/workflows
放置 Github Actions 所有的執行檔(.yml)，所有執行檔皆在台灣時間00:00(GMT+8)執行。

### kasm_workspace
放置 Kasm Workspace 相關的 VNC dockerfile，便於開發者在 Kasm Workspace 保持開箱即用的環境，鏡像中已安裝常見的開發工具。

### online_judge
放置 k12edu 團隊的程式解題網站的 dockerfile，方面管理。