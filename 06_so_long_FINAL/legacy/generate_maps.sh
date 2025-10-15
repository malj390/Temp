#!/bin/bash
# filepath: ./generate_map.sh

rows=6
cols=6
outfile="${1}" # Use first argument or default to map.txt

# Start with an empty map
map=()

# Generate the borders (first and last row)
border=$(printf '1%.0s' $(seq 1 $cols))
map+=("$border")

# Generate inner rows
for ((i=2; i<rows; i++)); do
    row="1"
    for ((j=2; j<cols; j++)); do
        # Randomly choose 0 or 1 for inner cells
        if (( RANDOM % 3 )); then
            row+="0"
        else
            row+="1"
        fi
    done
    row+="1"
    map+=("$row")
done

# Add last border row
map+=("$border")

# Place S and E randomly in the inner area
s_row=$((RANDOM % (rows-2) + 1))
s_col=$((RANDOM % (cols-2) + 1))
e_row=$((RANDOM % (rows-2) + 1))
e_col=$((RANDOM % (cols-2) + 1))
while [[ $s_row -eq $e_row && $s_col -eq $e_col ]]; do
    e_row=$((RANDOM % (rows-2) + 1))
    e_col=$((RANDOM % (cols-2) + 1))
done

# Insert S and E
map[$s_row]=$(echo "${map[$s_row]}" | sed "s/./S/$((s_col+1))")
map[$e_row]=$(echo "${map[$e_row]}" | sed "s/./E/$((e_col+1))")

# Write to file
printf "%s\n" "${map[@]}" > "$outfile"
echo "Map saved to $outfile"
cat $outfile
