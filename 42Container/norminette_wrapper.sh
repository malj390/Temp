#!/bin/bash
if [ "$#" -eq 0 ]; then
    echo "Usage: norminette <file ...>"
    exit 1
fi
norminette.bin "$@"
