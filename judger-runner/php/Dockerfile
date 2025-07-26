ARG PHP_TAG=8.3-bookworm
FROM php:${PHP_TAG}

RUN apt-get update && \
    apt-get install -y python3.11 python3.11-venv python3.11-distutils && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir /app
WORKDIR /app
COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/php/test.php /app/test.php