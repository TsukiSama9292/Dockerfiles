ARG NET_TAG=8.0-alpine
FROM mcr.microsoft.com/dotnet/sdk:${NET_TAG}

RUN apk update && apk add --no-cache python3 py3-pip

RUN mkdir /app
WORKDIR /app
COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/net/test.cs /app/test.cs