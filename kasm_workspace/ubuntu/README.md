# Ubuntu (DinD)

## 用途
提供開發人員最佳技術實踐的環境  

## 具備軟體
1. Docker, Docker Compose (指令: docker-compose)
2. NVM 與 Node.js (預設 Node.js 22)
3. DBeaver 社群版
4. Postman
5. Discord
6. uv 套件管理
7. Chrome
8. VScode, Git

## 鏡像編譯(測試用)
```bash
docker build -f "dockerfile.jammy-dind-rolling-daily" -t "tsukisama9292/ubuntu-jammy-dind:1.17.0-rolling-daily" .
docker run --rm -it --shm-size=512m -p 6901:6901 -e VNC_PW=password tsukisama9292/ubuntu-jammy-dind:1.17.0-rolling-daily
```