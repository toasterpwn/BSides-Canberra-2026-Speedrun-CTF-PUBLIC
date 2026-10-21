FROM ubuntu:latest
RUN apt-get update && apt-get install -y gcc
WORKDIR /app
CMD ["gcc", "-fno-builtin-memcmp", "-O0", "-std=c99", "src.c", "-o", "chal"]
