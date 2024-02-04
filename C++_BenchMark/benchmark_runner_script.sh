#!/bin/bash

# Save the current directory
original_dir=$(pwd)

# Check if machine type is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <machine_type>"
    echo "machine_type: desktop or raspberry_pi"
    exit 1
fi

machine_type=$1

# Define core configurations based on machine type
if [ "$machine_type" == "desktop" ]; then
    # For desktop, use 1, 2, 4, 6, 8, and 16 cores
    core_configs=(1 2 4 6 8 16)
elif [ "$machine_type" == "raspberry_pi" ]; then
    # For Raspberry Pi, use 1, 2, 4 cores (assuming Raspberry Pi has up to 4 cores)
    core_configs=(1 2 4 6 8)
else
    echo "Invalid machine type: $machine_type"
    echo "Please specify 'desktop' or 'raspberry_pi'"
    exit 2
fi

# Change to the build directory where the executable is located
# Ensure the build directory path is correct relative to this script's location
cd build || { echo "Failed to enter the build directory"; exit 3; }

# Function to generate core string for taskset, adjusting based on machine type
generate_core_string() {
    local core_count=$1
    local core_string=""
    local core_index=0
    if [ "$machine_type" == "desktop" ]; then
        for ((i=0; i<core_count; i++)); do
            if [ $i -eq 0 ]; then
                core_string="$core_index"
            else
                core_index=$((core_index + 2)) # Skip to the next physical core
                core_string="$core_string,$core_index"
            fi
        done
    elif [ "$machine_type" == "raspberry_pi" ]; then
        for ((i=0; i<core_count; i++)); do
            if [ $i -eq 0 ]; then
                core_string="$i"
            else
                core_string="$core_string,$i"
            fi
        done
    fi
    echo $core_string
}

# Main loop to execute the benchmark with varying core counts
for cores in "${core_configs[@]}"; do
    core_string=$(generate_core_string $cores)
    for ((i=1; i<=103; i++)); do
        echo "Running with $cores core(s): iteration $i"
        taskset -c $core_string ./mpbenchmark 3 $cores
    done
done

# Return to the original directory
cd "$original_dir"

echo "Benchmark completed."
