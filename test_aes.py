#!/usr/bin/env python3
import subprocess
with open('input_vectors.txt') as f:
    lines = f.readlines()
for line in lines:
    output = subprocess.run(['./aes_sample', line], stdout=subprocess.PIPE).stdout.decode('utf-8')
    filtered = []
    for s in output.split("\n"):
        if len(s) > 0:
            print(f"S:{s}")
            filtered.append(s)
