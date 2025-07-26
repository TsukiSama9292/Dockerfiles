ARG KOTLIN_TAG=1.4-alpine
FROM zenika/kotlin:${KOTLIN_TAG}

RUN apk update && apk add --no-cache python3 py3-pip

RUN mkdir /app
WORKDIR /app
COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/kotlin/test.kt /app/test.kt