Open Docker
# Dockerfile (run in cwd)

Create the next file with the name `Dockerfile` and place it within the project directory.

```bash
# Mimics the 42 Málaga environment for Valgrind consistency
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# Install 42-style toolchain
RUN apt update && apt install -y \
    build-essential \
    clang \
    make \
    valgrind \
    gdb \
    zsh \
    git \
    curl \
    wget \
    python3 \
    python3-pip \
    && apt clean

# Optional: match specific compiler versions
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100

# Create workspace
WORKDIR /app
```

Once in the **project directory** run the next command depending on the OS.

```bash
docker build -t ubuntu-valgrind .
```
## Windows (Powershell)

To install the docker container write in Powershell the next command.

```bash
docker run -it --rm -v ${PWD}:/app ubuntu-valgrind bash
```

## WSL (Ubuntu)

```bash
docker run -it --rm -v "$(pwd)":/app ubuntu-valgrind bash
```

