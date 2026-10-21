FROM ubuntu:latest
RUN apt-get update && apt-get install -y gcc
WORKDIR /app
CMD ["gcc", "-O0", "-o", "chal", "src.c"]
