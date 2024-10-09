#!/usr/bin/env python3
import sys
import os
import time

# find sound/samples/*custom* -name '*.aiff' | while read filename; do     python3 tools/append_aiffc_table.py "$filename"; done

# Get the filename from the first command line argument
if len(sys.argv) < 2:
    print("Usage: {} <filename>".format(sys.argv[0]))
    sys.exit(1)
filename = sys.argv[1]

# check if the binary file contains the string 'VADPCMCODES', and if so print that it was already found and exit
with open(filename, 'rb') as f:
    content = f.read()
if b'VADPCMCODES' in content:
    print('Already contains a table for ' + filename + '. Exiting.')
    sys.exit(0)

# run the program ./tools/tabledesign on the specified filename and capture the output
import subprocess
command = ['./tools/tabledesign', '-s', '1', filename]
result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
output = result.stdout.decode('utf-8').strip()

# split the output by whitespace
words = output.split()

# calculate header info
size = len(words) * 2 + 18
unknown = 0x0b
version = 1

# append the chunk header
chunk = b''
chunk += b'APPL'
chunk += size.to_bytes(4, 'big', signed=True)
chunk += b'stoc'
chunk += unknown.to_bytes(1, 'big', signed=False)
chunk += b'VADPCMCODES'
chunk += version.to_bytes(2, 'big', signed=False)

# convert each word to a signed 16 bit integer and append them to content
for word in words:
    value = int(word)
    chunk += value.to_bytes(2, 'big', signed=True)

# find the index of the first instance of 'SSND'
index = content.find(b'SSND')
if index == -1:
    print("Couldn't find 'SSND' for ' + filename + '. Aborting.")
    sys.exit(1)

if size != len(chunk) - 8:
    print('Failed to generate the correct size for ' + filename)
    sys,exit(1)

# insert the chunk before 'SSND'
content = content[:index] + chunk + content[index:]

# write the modified content to the binary file
with open(filename, 'wb') as f:
    f.write(content)
