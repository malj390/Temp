#!/bin/bash

# ==============================================================================
# Docker Container Runner for 42 Environment
# ==============================================================================
#
# This script builds and runs the 42-like Docker container.
#
# Features:
# - Builds the Docker image if it doesn't exist.
# - Mounts the current working directory to `/app` in the container.
# - Passes the current user's ID and group ID to the container to avoid
#   file permission issues.
# - Removes the container after exiting.
# - Supports bash and fish shell history persistence.
#

# --- Configuration ---
IMAGE_NAME="42-env"
DOCKERFILE="Dockerfile"

# --- Build the Docker image ---
if ! docker image inspect "$IMAGE_NAME" &> /dev/null; then
    echo "Building Docker image '$IMAGE_NAME' ભા"
    docker build -t "$IMAGE_NAME" \
        --build-arg USER_ID=$(id -u) \
        --build-arg GROUP_ID=$(id -g) \
        -f "$DOCKERFILE" .
fi

# --- Create history files on host if they don't exist ---
touch "$HOME/.bash_history"
touch "$HOME/.zsh_history"
mkdir -p "$HOME/.local/share/fish"
touch "$HOME/.local/share/fish/fish_history"

# --- Run the Docker container ---
echo "Running Docker container ભા"
docker run -it --rm --hostname 42container \
    -v "$(pwd)":/app \
    -v "$HOME/.bash_history:/home/42user/.bash_history" \
    -v "$HOME/.zsh_history:/home/42user/.zsh_history" \
    -v "$HOME/.local/share/fish/fish_history:/home/42user/.local/share/fish/fish_history" \
    -v "$HOME/.config/fish/config.fish:/home/42user/.config/fish/config.fish" \
    -v "$HOME/.config/fish/functions:/home/42user/.config/fish/functions" \
    -v "$HOME/.config/fish/completions:/home/42user/.config/fish/completions" \
    -v "$HOME/.config/fish/conf.d:/home/42user/.config/fish/conf.d" \
    -v "$HOME/.gitconfig:/home/42user/.gitconfig" \
    -v $SSH_AUTH_SOCK:/ssh-agent -e SSH_AUTH_SOCK=/ssh-agent \
    -e HISTFILE=/home/42user/.bash_history \
    "$IMAGE_NAME" \
    "$@"
