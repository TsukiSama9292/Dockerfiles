FROM ubuntu:22.04

# 安裝必要工具（加入 gnupg）
RUN apt-get update && \
    apt-get install -y \
    curl \
    wget \
    gnupg \
    lsb-release

# 匯入 PostgreSQL 的 GPG 金鑰
RUN wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | apt-key add -

# 加入 PostgreSQL 的 APT 套件庫
RUN echo "deb http://apt.postgresql.org/pub/repos/apt $(lsb_release -cs)-pgdg main" > /etc/apt/sources.list.d/pgdg.list

# 安裝 PostgreSQL 16 client
RUN apt-get update && \
    apt-get install -y postgresql-client-16
