FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Install all dependencies including MLX42 requirements
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-10 \
    clang-12 \
    make \
    cmake \
    valgrind \
    git \
    vim \
    gdb \
    libx11-dev \
    libxext-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxcursor-dev \
    libxfixes-dev \
    libglfw3-dev \
    libglfw3 \
    libbsd-dev \
    xorg-dev \
    libglu1-mesa-dev \
    && rm -rf /var/lib/apt/lists/*

# Set default compiler to match 42 (clang)
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang-12 100

WORKDIR /project

CMD ["/bin/bash"]
