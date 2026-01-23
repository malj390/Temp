#!/bin/bash

# ==============================================================================
# Shell Alias/Function Setup for 42 Docker Container
# ==============================================================================
#
# This script adds a '42' function to your .bashrc, .zshrc, and Fish
# config files to make it easy to run the 42 Docker container from any
# terminal.
#
# The function will be added only if it doesn't already exist.
#

# --- Configuration ---
ALIAS_NAME="42"
RUN_SH_PATH="$(pwd)/run.sh"

# --- Add to .bashrc ---
if [ -f "$HOME/.bashrc" ]; then
    if ! grep -q "function $ALIAS_NAME()" "$HOME/.bashrc"; then
        echo "Adding '$ALIAS_NAME' function to ~/.bashrc..."
        echo -e "\n# Function to run the 42 Docker container" >> "$HOME/.bashrc"
        echo "function $ALIAS_NAME() {" >> "$HOME/.bashrc"
        echo "    \"$RUN_SH_PATH\" \"\$@\"" >> "$HOME/.bashrc"
        echo "}" >> "$HOME/.bashrc"
    else
        echo "'$ALIAS_NAME' function already exists in ~/.bashrc."
    fi
fi

# --- Add to .zshrc ---
if [ -f "$HOME/.zshrc" ]; then
    if ! grep -q "function $ALIAS_NAME()" "$HOME/.zshrc"; then
        echo "Adding '$ALIAS_NAME' function to ~/.zshrc..."
        echo -e "\n# Function to run the 42 Docker container" >> "$HOME/.zshrc"
        echo "function $ALIAS_NAME() {" >> "$HOME/.zshrc"
        echo "    \"$RUN_SH_PATH\" \"\$@\"" >> "$HOME/.zshrc"
        echo "}" >> "$HOME/.zshrc"
    else
        echo "'$ALIAS_NAME' function already exists in ~/.zshrc."
    fi
fi

# --- Add to Fish config ---
if [ -d "$HOME/.config/fish" ]; then
    if ! grep -q "function $ALIAS_NAME" "$HOME/.config/fish/config.fish"; then
        echo "Adding '$ALIAS_NAME' function to ~/.config/fish/config.fish..."
        echo -e "\n# Function to run the 42 Docker container" >> "$HOME/.config/fish/config.fish"
        echo "function $ALIAS_NAME" >> "$HOME/.config/fish/config.fish"
        echo "    \"$RUN_SH_PATH\" \$argv" >> "$HOME/.config/fish/config.fish"
        echo "end" >> "$HOME/.config/fish/config.fish"
    else
        echo "'$ALIAS_NAME' function already exists in ~/.config/fish/config.fish."
    fi
else
    mkdir -p "$HOME/.config/fish"
    echo "Adding '$ALIAS_NAME' function to ~/.config/fish/config.fish..."
    echo -e "\n# Function to run the 42 Docker container" >> "$HOME/.config/fish/config.fish"
    echo "function $ALIAS_NAME" >> "$HOME/.config/fish/config.fish"
    echo "    \"$RUN_SH_PATH\" \$argv" >> "$HOME/.config/fish/config.fish"
    echo "end" >> "$HOME/.config/fish/config.fish"
fi

echo -e "\nPlease restart your terminal or source your shell configuration files for the changes to take effect."
