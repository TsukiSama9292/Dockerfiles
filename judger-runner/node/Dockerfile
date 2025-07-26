ARG NODE_TAG=lts-alpine
FROM node:${NODE_TAG}

# 安裝基本工具與 bash
RUN apk update && apk add --no-cache python3 py3-pip bash

# 安裝 typescript
RUN npm install -g typescript

# 建立目錄
RUN mkdir /app
WORKDIR /app

# 拷貝程式碼與設定
COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/node/test.js /app/test.js
COPY judger-runner/node/test.ts /app/test.ts