#!/bin/sh

set -xe

CFLAGS=`pkg-config --cflags gtk4`
LIBS=`pkg-config --libs gtk4`

gcc -o eyver main.c $CFLAGS $LIBS
