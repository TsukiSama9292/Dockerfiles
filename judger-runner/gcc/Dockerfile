ARG GCC_TAG=15-bookworm
FROM gcc:${GCC_TAG}

RUN apt-get update && \
    apt-get install -y python3.11 python3.11-venv python3.11-distutils && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir /app
WORKDIR /app

COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/caller.py /app/caller.py
COPY judger-runner/gcc/test.c /app/test.c
COPY judger-runner/gcc/test.cpp /app/test.cpp