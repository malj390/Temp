#!/bin/bash

# Usage: ./generate_map.sh <rows> <cols> <output_file>
if [ "$#" -ne 3 ]; then
    echo "Usage: $0 <rows> <cols> <output_file>"
    exit 1
fi

ROWS=$1
COLS=$2
OUTFILE=$3

# Minimum size check
if [ "$ROWS" -lt 5 ] || [ "$COLS" -lt 5 ]; then
    echo "Rows and columns must be at least 5."
    exit 1
fi

# Create empty map with walls
declare -A MAP
for ((i=0; i<ROWS; i++)); do
    for ((j=0; j<COLS; j++)); do
        if [ "$i" -eq 0 ] || [ "$i" -eq $((ROWS-1)) ] || [ "$j" -eq 0 ] || [ "$j" -eq $((COLS-1)) ]; then
            MAP[$i,$j]=1
        else
            MAP[$i,$j]=0
        fi
    done
done

# Randomly place walls inside, ensuring connectivity
# Use randomized DFS to carve out a single connected area
function dfs() {
    local x=$1
    local y=$2
    MAP[$x,$y]=0
    local dirs=("0 1" "1 0" "0 -1" "-1 0")
    # Shuffle directions
    for i in {0..3}; do
        r=$((RANDOM % 4))
        tmp=${dirs[$i]}
        dirs[$i]=${dirs[$r]}
        dirs[$r]=$tmp
    done
    for dir in "${dirs[@]}"; do
        dx=$(echo $dir | cut -d' ' -f1)
        dy=$(echo $dir | cut -d' ' -f2)
        nx=$((x + dx * 2))
        ny=$((y + dy * 2))
        if [ "$nx" -gt 0 ] && [ "$nx" -lt $((ROWS-1)) ] && [ "$ny" -gt 0 ] && [ "$ny" -lt $((COLS-1)) ]; then
            if [ "${MAP[$nx,$ny]}" = "1" ]; then
                MAP[$((x + dx)),$((y + dy))]=0
                dfs $nx $ny
            fi
        fi
    done
}

# Fill interior with walls
for ((i=1; i<ROWS-1; i++)); do
    for ((j=1; j<COLS-1; j++)); do
        MAP[$i,$j]=1
    done
done

# Start DFS from random position
sx=$((RANDOM % (ROWS-2) + 1))
sy=$((RANDOM % (COLS-2) + 1))
dfs $sx $sy

# Place collectibles (C) randomly in empty spaces
num_collectibles=$(( (ROWS * COLS) / 20 + 1 ))
placed=0
while [ $placed -lt $num_collectibles ]; do
    x=$((RANDOM % (ROWS-2) + 1))
    y=$((RANDOM % (COLS-2) + 1))
    if [ "${MAP[$x,$y]}" = "0" ]; then
        MAP[$x,$y]="C"
        placed=$((placed+1))
    fi
done


# Place exit (E) at a random empty location
while true; do
    x=$((RANDOM % (ROWS-2) + 1))
    y=$((RANDOM % (COLS-2) + 1))
    if [ "${MAP[$x,$y]}" = "0" ]; then
        MAP[$x,$y]="E"
        break
    fi
done

# Place player (P) at a random empty location
while true; do
    x=$((RANDOM % (ROWS-2) + 1))
    y=$((RANDOM % (COLS-2) + 1))
    if [ "${MAP[$x,$y]}" = "0" ]; then
        MAP[$x,$y]="P"
        break
    fi
done

# Output map to file
> "$OUTFILE"
for ((i=0; i<ROWS; i++)); do
    line=""
    for ((j=0; j<COLS; j++)); do
        val=${MAP[$i,$j]}
        line+="$val"
    done
    echo "$line" >> "$OUTFILE"
done