# ============================================
# 42-Like Environment for C Projects & Testing
# Ubuntu 22.04 LTS - Matching 42 Málaga versions
# ============================================

FROM ubuntu:22.04

LABEL maintainer="42-compatible environment" \
      description="Docker image replicating the 42 toolchain setup for consistent testing (Valgrind, Norminette, compilers, shells, etc.)"

ENV DEBIAN_FRONTEND=noninteractive

# ---------------------------
# System and basic toolchain
# ---------------------------
RUN apt update && apt install -y \
    build-essential \
    clang-12 \
    gcc-10 g++-10 \
    make \
    valgrind \
    gdb \
    lldb-12 \
    zsh \
    fish \
    git \
    curl \
    wget \
    bash \
    python3 python3-pip \
    ruby-full \
    perl \
    openjdk-17-jdk \
    nodejs npm \
    && apt clean && rm -rf /var/lib/apt/lists/*

# ---------------------------
# Set default compilers
# ---------------------------
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang-12 100 \
 && update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++-12 100 \
 && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 90 \
 && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 90

# ---------------------------
# Install Norminette
# ---------------------------
RUN pip3 install --upgrade pip==22.0.2 \
 && pip3 install norminette==3.3.58

# ---------------------------
# Verify core tool versions
# ---------------------------
RUN echo "==== Installed tool versions ====" && \
    echo "cc: $(cc --version | head -n 1)" && \
    echo "gcc: $(gcc --version | head -n 1)" && \
    echo "clang: $(clang --version | head -n 1)" && \
    echo "python3: $(python3 --version)" && \
    echo "pip3: $(pip3 --version)" && \
    echo "make: $(make --version | head -n 1)" && \
    echo "valgrind: $(valgrind --version)" && \
    echo "norminette: $(norminette --version)" && \
    echo "git: $(git --version)" && \
    echo "curl: $(curl --version | head -n 1)" && \
    echo "wget: $(wget --version | head -n 1)" && \
    echo "bash: $(bash --version | head -n 1)" && \
    echo "zsh: $(zsh --version)" && \
    echo "fish: $(fish --version)" && \
    echo "gdb: $(gdb --version | head -n 1)" && \
    echo "lldb: $(lldb --version | head -n 1)" && \
    echo "ruby: $(ruby --version)" && \
    echo "node: $(node --version)" && \
    echo "java: $(java -version 2>&1 | head -n 1)" && \
    echo "================================="

# ---------------------------
# Default working directory
# ---------------------------
WORKDIR /app

# Default shell: zsh
CMD ["/usr/bin/zsh"]
