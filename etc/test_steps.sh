#!/usr/bin/env bash

previous_value=0
steps=0
clear
echo "steps: ${steps}"

while true; do
    current_value=$(sudo gpioget gpiochip0 24)

    if (( ${current_value} > ${previous_value} )); then
        steps=$((steps + 1))
        clear
        echo "steps: ${steps}"
    fi

    previous_value=${current_value}
    sleep 0.03
done
