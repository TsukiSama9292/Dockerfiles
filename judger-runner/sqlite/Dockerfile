ARG ALPINE_ARG=3.18
FROM alpine:${ALPINE_ARG}

RUN apk update && apk add --no-cache \
    build-base \
    wget \
    python3 \
    py3-pip \
    sqlite

RUN mkdir /app
WORKDIR /app
COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/sqlite/test.db /app/test.db
COPY judger-runner/sqlite/test.sql /app/test.sql