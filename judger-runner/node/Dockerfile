ARG NODE_TAG=lts-bookworm-slim
FROM node:${NODE_TAG}

RUN apt-get update && \
    apt-get install -y python3.11 python3.11-venv python3.11-distutils && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir /app
WORKDIR /app
COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/node/test.js /app/test.js