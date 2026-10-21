from pwn import *
from config import REMOTE_ADDR, REMOTE_PORT

REMOTE = 0  # Change to 1 to run the exploit on the remote instance

e = context.binary = ELF("./chal")

if REMOTE:
    p = remote(REMOTE_ADDR, REMOTE_PORT)
else:
    p = e.process()


def login(password):
    assert len(password) == 0x10
    p.sendafter(b"Login: ", password)
    res = p.recvline().decode()
    return res


res = login(b"A" * 0x10)
print(res)
