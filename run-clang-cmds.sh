#!/bin/env bash 

find . -name "*.c" -exec clang-format -i {} \;
run-clang-tidy -p ./build

