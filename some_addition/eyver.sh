#!/bin/bash

SCRIPT_DIR="$(dirname "$(realpath "$0")")"

while true; do
    sleep $1

    status=$(playerctl status)

    if [ "$status" != "Paused" ]; then
        playerctl pause
    fi

    # $SCRIPT_DIR/eyver <msg> [font name]
    $SCRIPT_DIR/../eyver "It's time to rest!"

    if [ "$status" != "Paused" ]; then
        playerctl play
    fi
done
