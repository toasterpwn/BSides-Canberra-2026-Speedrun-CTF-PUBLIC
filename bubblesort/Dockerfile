FROM ubuntu:latest
RUN apt-get update && apt-get install -y socat && rm -rf /var/lib/apt/lists/*
RUN useradd -m ctf
COPY chal /home/ctf/
COPY flag.txt /home/ctf
USER ctf
WORKDIR /home/ctf
RUN chmod +x /home/ctf/chal
CMD ["socat", "TCP-LISTEN:1337,reuseaddr,fork", "EXEC:/home/ctf/chal"]
