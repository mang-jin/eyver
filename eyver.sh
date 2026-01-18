#!/bin/bash

SCRIPT_DIR="$(dirname "$(realpath "$0")")"

while true; do
    sleep $1
    # $SCRIPT_DIR/eyver <msg> [font name]
    $SCRIPT_DIR/eyver "It's time to rest!"
done
