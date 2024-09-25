#!/bin/bash

set -eu

mkdir -p build 

cmake -S . \
			-B build \
			-G Ninja \
			-DCMAKE_CXX_COMPILER=clang++ \
			-DCMAKE_C_COMPILER=clang \
			-DCMAKE_BUILD_TYPE=Debug \
			-DCMAKE_EXPORT_COMPILE_COMMANDS=1 
cmake --build build --parallel $(nproc)
cp -f build/compile_commands.json .

if [ $1 == "run" ]; then
	echo -e "\n"
	./build/wordly -n 3
fi
