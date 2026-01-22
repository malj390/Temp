# 42 Environment Docker Container Manual

This document provides instructions on how to set up and use the Docker container that replicates the 42 school's development environment.

## 1. Prerequisites

- **Docker:** You must have Docker installed on your system.

## 2. Building the Docker Image

The `run.sh` script will automatically build the Docker image for you the first time you run it. The image will be named `42-env`.

If you need to rebuild the image for any reason (e.g., after modifying the `Dockerfile`), you can run:

```bash
./run.sh
```

The script will detect that the image already exists and will not rebuild it. To force a rebuild, you must first remove the existing image:

```bash
docker rmi 42-env
```

Then run the script again.

## 3. Running the Container

To run the container, execute the `run.sh` script from your project's directory:

```bash
./run.sh
```

This will start an interactive session in the container. The key features of this setup are:

- **Simplified Prompt:** The container's hostname is set to `42container`, and the username is `42user`, so your shell prompt will look like `42user@42container /app>`.
- **Project Directory Access:** Your current working directory is mounted at `/app` inside the container. You can access all your project files there.
- **User Permissions:** The container runs with your user and group ID, so any files you create will have the correct ownership.
- **Persistent Shell History:** Your `bash` and `fish` shell histories are shared between your host machine and the container.

### 3.1. Using Different Shells

By default, the container starts with `zsh`. You can specify a different shell when you run the container:

- **Bash:**
  
  ```bash
  ./run.sh bash
  ```

- **Fish:**
  
  ```bash
  ./run.sh fish
  ```

## 4. Easy Access with a Shell Shortcut

To make it easy to start the container from any terminal, a `setup_alias.sh` script is provided. This script will add a `42` function to your `.bashrc`, `.zshrc`, and `~/.config/fish/config.fish` files.

To run the script, execute the following command from the same directory as the `Dockerfile`:

```bash
./setup_alias.sh
```

The script will automatically detect your shell configuration files and add the `42` function if it doesn't already exist.

After running the script, restart your terminal or source your shell configuration files:

- **For Bash:** `source ~/.bashrc`
- **For Zsh:** `source ~/.zshrc`
- **For Fish:** `source ~/.config/fish/config.fish`

Now you can simply run `42` from any directory to start the container in that directory. For example:

```bash
cd /path/to/my/project
42
```

This will launch the container with `/path/to/my/project` mounted as `/app`. You can also specify a shell:

```bash
42 fish
```

## 5. Customizing the Fish Shell

You can add your own custom functions and settings to the `fish` shell inside the container.

1. Create a `~/.config/fish/config.fish` file on your host machine if you don't already have one. This file will store your custom `fish` functions and settings.

2. The `run.sh` script is already configured to mount your host's `~/.config/fish/config.fish` file into the container at `/home/42user/.config/fish/config.fish`. Any changes you make to your local `config.fish` will therefore be reflected inside the container.
