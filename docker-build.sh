#!/bin/bash

set -ex

docker build --tag wordly .
docker run -it --rm --volume ./docker-build:/app/build --name wordly wordly
echo -e "\nBuilt binaries are written to docker-build/"
