FROM ubuntu:latest

RUN apt-get update && apt-get install -y socat && rm -rf /var/lib/apt/lists/*

RUN useradd -m ctf

COPY catv2 /home/ctf/
COPY flag.txt /

RUN chown root:root /home/ctf/catv2 /flag.txt \
    && chmod 4755 /home/ctf/catv2 \
    && chmod 400 /flag.txt

USER ctf
WORKDIR /home/ctf

CMD ["socat", "TCP-LISTEN:5000,reuseaddr,fork", "EXEC:/bin/bash -li,pty,stderr,setsid,sigint,sane"]
