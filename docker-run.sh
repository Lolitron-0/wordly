#!/bin/bash

docker build --tag wordly .
docker run -it --rm --volume ./docker-build:/app/build --name wordly wordly
