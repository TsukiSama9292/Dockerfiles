ARG GCC_TAG=15-bookworm
FROM gcc:${GCC_TAG}

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
        make \
        cmake \
        python3 \
        python3-venv \
        python3-distutils \
        time \
        valgrind && \
    rm -rf /var/lib/apt/lists/*

# Create app directory
RUN mkdir /app
WORKDIR /app

# Copy C++ OJ runner files
COPY judger-runner/c++/* /app/

# Set default command
CMD ["make", "help"]
