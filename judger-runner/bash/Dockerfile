ARG BASH_TAG=5.3
FROM bash:${BASH_TAG}

RUN apk update && \
    apk add --no-cache \
    python3 \
    py3-pip

RUN mkdir /app
WORKDIR /app
COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/bash/test.sh /app/test.sh
RUN chmod +x /app/test.sh