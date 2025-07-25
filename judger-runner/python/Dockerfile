ARG PYTHON_TAG=3.12-slim
FROM python:${PYTHON_TAG}

RUN mkdir /app
WORKDIR /app
COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/python/test.py /app/test.py