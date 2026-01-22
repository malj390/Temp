## File Purposes

* **`Dockerfile`**: Defines the Docker image for a 42-like development environment. It starts from an Ubuntu 22.04 base and installs all the necessary tools like `clang`, `gcc`, `make`, `valgrind`, `norminette`, etc. It also creates a non-root user to avoid permission issues.
* **`norminette_wrapper.sh`**: A wrapper script to fix a crash with `norminette`. It calls the original `norminette.bin` with the provided arguments.
* **`run.sh`**: This script builds the Docker image (if it doesn't exist) and runs the container. It mounts the current working directory, shell history files, and git configuration into the container.
* **`setup_alias.sh`**: This script creates a shell function (alias) named `42` in the user's shell configuration file (`.bashrc`, `.zshrc`, or `config.fish`). This allows the user to run the Docker container from any directory.
* 

# 42 Environment Docker Container

This repository provides a Docker-based development environment that replicates the setup used at 42 schools. It allows you to work on your projects in a consistent and predictable environment, regardless of your host operating system.

> **Important Note for Graphical Projects:** This container is designed for terminal-based projects and does not have a graphical environment. Projects that require a graphical interface (like those using MiniLibX, such as `so_long` or `cub3d`) will not run out-of-the-box. Tools like `valgrind` may also behave differently with graphical applications due to the lack of an X11 connection to the host.

## Features

- **OS:** Ubuntu 22.04, matching the 42 network environment.
- **C/C++ Development:** `clang-12` (default `cc`), `gcc-10`, `make`, `gdb`, `lldb-12`, `valgrind`.
- **42 Tools:** `norminette` (v3.3.58).
- **Shells:** `zsh` (default), `bash`, and `fish`.
- **Project Directory Access:** Your current working directory is mounted inside the container.
- **User Permissions:** Runs with your user and group ID to avoid file ownership issues.
- **Persistent Shell History:** Your `bash`, `zsh`, and `fish` shell histories are shared between your host and the container.
- **Git Integration:**
  - **Authentication:** Forwards your host's SSH agent to the container for secure `git` operations.
  - **Identity:** Uses your host's `.gitconfig` file, so your commits are correctly authored.
- **Other Development Tools:** Includes `python3`, `ruby`, `perl`, `nodejs`, `java`, and more.

## Prerequisites

- **Docker:** You must have Docker installed and running on your system.
- **Git:** Your name and email should be configured in your global `.gitconfig` file (`~/.gitconfig`).

## How it Works: The `42` Command

The main goal of this project is to provide a seamless workflow. The intended use is to `cd` into one of your 42 project directories and simply run the `42` command.

When you do this, you will be placed inside a container that has all the necessary tools for your project (`cc`, `make`, `valgrind`, etc.). The directory you were in is now mounted at `/app` inside the container, so you can compile your code, run your tests, and use `git` as if you were on a 42 school machine.

## Getting Started: A Step-by-Step Guide

### Step 1: Initial Container Setup

Before you can use the `42` command, you need to build the Docker image and set up the shell shortcut.

1. **Run the script:** Navigate to this project directory (the one containing the `Dockerfile`) and run the following command:
   
   ```bash
   ./run.sh
   ```
   
   You must run this command from this specific directory because it needs to find the `Dockerfile` to build the image. The first time you run this, it will take a few minutes to build the Docker image. The script will then drop you into a shell inside the container. You can simply `exit` for now.

2. **Set up the shortcut:** To create the convenient `42` command, run the setup script from the same directory:
   
   ```bash
   ./setup_alias.sh
   ```
   
   This script adds a function named `42` to your shell's configuration file (`.zshrc`, `.bashrc`, or `config.fish`). This function is a shortcut that calls the `./run.sh` script from this project's directory, allowing you to launch the container from anywhere on your system.

3. **Restart your terminal:** For the `42` command to become active, you need to either restart your terminal or "source" your shell's configuration file (e.g., `source ~/.zshrc`).

### Step 2: Your Daily Workflow

Once the setup is complete, your workflow will be simple:

1. Open a terminal and navigate to the 42 project you want to work on.
   
   ```bash
   cd ~/path/to/your/42_project
   ```

2. Run the `42` command.
   
   ```bash
   42
   ```

3. You are now inside the container! Your project files are right there, in the `/app` directory. You can compile your code, run `norminette`, use `valgrind`, and `git push` your changes, all using the familiar 42 environment.
   
   ```bash
   # Inside the container
   42user@42container /app> ls
   Makefile  includes/  libft/  sources/
   42user@42container /app> make
   ...
   ```

### Step 3: Exiting the Container

To exit the container's interactive session, you can either run the `exit` command or press `Ctrl+D`. The container will automatically stop and remove itself.

## Container Management

### Checking if the Container is Running

If you are running the

 `42` command in one terminal, you can verify that the container is active from another terminal using `docker ps`. Since the container is configured with `--rm` (remove on exit), it will only appear in this list while it's actively running an interactive session.

```bash
docker ps
```

### Forcing a Rebuild

If you modify the `Dockerfile` or suspect the Docker image is corrupted, you may need to force a rebuild.

1. **Remove the existing image:**
   
   ```bash
   docker rmi 42-env
   ```

2. **Run the container again:**
   The next time you run `./run.sh` or the `42` command, the script will detect that the image is missing and build a new one.
   
   ```bash
   42
   ```
