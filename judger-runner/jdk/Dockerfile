FROM debian:bookworm-slim

ARG JDK_TAG=17

RUN apt-get update && \
    apt-get install -y \
        openjdk-${JDK_TAG}-jdk \
        python3.11 \
        python3.11-venv \
        python3.11-distutils && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir /app
WORKDIR /app

COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/caller.py /app/caller.py
COPY judger-runner/jdk/Test.java /app/Test.java