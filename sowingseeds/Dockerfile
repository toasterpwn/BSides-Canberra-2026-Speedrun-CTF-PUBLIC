FROM ubuntu:latest

RUN apt-get update && apt-get install -y socat && rm -rf /var/lib/apt/lists/*

RUN useradd -m ctf

COPY sowingseeds /home/ctf/
COPY flag.txt /home/ctf

RUN chmod 755 /home/ctf/sowingseeds \
    && chmod 444 /home/ctf/flag.txt

USER ctf
WORKDIR /home/ctf

CMD ["socat", "TCP-LISTEN:1337,reuseaddr,fork", "EXEC:/home/ctf/sowingseeds"]
