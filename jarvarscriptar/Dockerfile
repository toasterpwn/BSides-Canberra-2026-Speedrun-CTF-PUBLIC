FROM ubuntu:latest
RUN apt-get update && apt-get install -y socat python3 nodejs && rm -rf /var/lib/apt/lists/*
RUN useradd -m ctf
COPY chal.py /home/ctf/
COPY flag.txt /home/ctf
RUN chmod +x /home/ctf/chal.py
USER ctf
WORKDIR /home/ctf
CMD ["socat", "TCP-LISTEN:1337,reuseaddr,fork", "EXEC:/home/ctf/chal.py"]
