#!/bin/bash

# $chmod u+x load
# ls -l load

function all() {
    cd build
    cmake ..
    cmake --build .
    ./http_server
}

case "$1" in
    all)
        all
        ;;
esac