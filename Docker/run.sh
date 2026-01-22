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

# --- Run the Docker container ---
echo "Running Docker container ભા"
docker run -it --rm --hostname 42container \
    -v "$(pwd)":/app \
    -v "$HOME/.bash_history:/home/42user/.bash_history" \
    -e HISTFILE=/home/42user/.bash_history \
    "$IMAGE_NAME" \
    "$@"
