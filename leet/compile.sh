#!/bin/sh
set -eu

docker build --platform linux/amd64 -f compile.dockerfile -t chal-build .
docker run --rm --platform linux/amd64 -v "$PWD:/app" chal-build
