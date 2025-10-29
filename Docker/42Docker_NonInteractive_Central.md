Open Docker
# Dockerfile

Create the next file with the name `Dockerfile`.

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
# Keep your Dockerfile in a central folder

For example:

`D:\docker_envs\ubuntu-valgrind\ └── Dockerfile`

Build the image once:

`cd D:\docker_envs\ubuntu-valgrind docker build -t ubuntu-valgrind .`

Now that image exists system-wide.

# Run the container from any project folder

Let’s say you’re in:

`07_Philosophers\`

Run:

### PowerShell:

```bash
docker run -it --rm -v ${PWD}:/project  -w /project ubuntu-valgrind bash
```
### Bash / WSL:
```
docker run -it --rm -v "$(pwd)":/project -w /project ubuntu-valgrind bash
```

### Explanation

- `-v ${PWD}:/project`  
    Mounts **your current folder** into the container at `/project`.
- `-w /project`  
    Overrides the `WORKDIR` from the Dockerfile so you start directly there.
- The container still uses the environment defined by your central `Dockerfile`.