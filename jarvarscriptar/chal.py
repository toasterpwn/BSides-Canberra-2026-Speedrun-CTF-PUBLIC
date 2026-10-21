#!/usr/bin/env python3
import subprocess

while True:
    js_str = input("js> ")

    if len(js_str.strip()) == 0:
        break

    if any(c in js_str for c in "()"):
        print("no")
        continue

    
    result = subprocess.run([
        "node", 
        "-e",
        f"console.log({js_str})"
    ], capture_output=True)

    print("stdout:", result.stdout.hex())
    print("stderr:", result.stderr.hex())