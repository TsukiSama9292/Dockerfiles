ARG RUBY_TAG=3.4
FROM ruby:${RUBY_TAG}

RUN mkdir /app
WORKDIR /app
COPY judger-runner/runner.py /app/runner.py
COPY judger-runner/ruby/test.rb /app/test.rb