ARG RUST_TAG=latest
FROM rust:${RUST_TAG}

RUN mkdir /app
WORKDIR /app
COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/rust/test.rs /app/test.rs