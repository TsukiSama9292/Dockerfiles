FROM debian:bookworm-slim
ARG JDK_TAG
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y wget gnupg ca-certificates curl && \
    mkdir -p /usr/share/keyrings && \
    curl -s https://repos.azul.com/azul-repo.key | gpg --dearmor -o /usr/share/keyrings/azul.gpg

RUN echo "deb [signed-by=/usr/share/keyrings/azul.gpg] https://repos.azul.com/zulu/deb stable main" \
     > /etc/apt/sources.list.d/zulu.list

RUN apt-get update && \
    apt-get install -y zulu${JDK_TAG}-jdk python3.11 python3.11-venv python3.11-distutils && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir /app
WORKDIR /app

COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/jdk/Test.java /app/Test.java