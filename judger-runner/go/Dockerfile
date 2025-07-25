ARG GO_TAG=1.24-bookworm
FROM golang:${GO_TAG}

RUN mkdir /app
WORKDIR /app
COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/go/test.go /app/test.go