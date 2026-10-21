FROM ubuntu:latest
RUN apt-get update && apt-get install -y gcc
WORKDIR /app
CMD ["gcc", "-O0", "-no-pie", "-std=c99", "src.c", "-o", "chal"]
