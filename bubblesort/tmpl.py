from pwn import *
# from config import REMOTE_ADDR, REMOTE_PORT

REMOTE = 0  # Change to 1 to run the exploit on the remote instance

e = context.binary = ELF("./chal")

if REMOTE:
    p = remote(REMOTE_ADDR, REMOTE_PORT)
else:
    p = e.process()

def send_num(n):
    p.sendafter(b"number?", str(n).encode() + b"\n")
    p.recvuntil(b"got: ")
    return p.recvline()

def sort_nums(nums):
    for num in nums:
        send_num(num)
    send_num(66+1) 

    
    p.recvuntil(b"Before Sorting: ")
    before_sort = eval(p.recvline().decode())

    p.recvuntil(b"After Sorting: ")
    after_sort = eval(p.recvline().decode())
    
    return after_sort


res = sort_nums([5,4,3,2,1])
print(res)
