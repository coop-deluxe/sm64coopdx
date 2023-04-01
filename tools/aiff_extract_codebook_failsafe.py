#!/usr/bin/env python3
import sys
import os
import subprocess

# example before: tools/aiff_extract_codebook sound/samples/sfx_custom_luigi/00.aiff >build/us_pc/sound/samples/sfx_custom_luigi/00.table

s_size = 0

# check arguments
if len(sys.argv) != 4:
    print(sys.argv[0] + ': was passed the incorrect number of arguments: ' + str(sys.argv), file=sys.stderr)
    exit(1)

# get arguments
a_cmd = sys.argv[1]
a_input = sys.argv[2]
a_output = sys.argv[3]

# validate input
if not os.path.isfile(a_input):
    print(sys.argv[0] + ': original input file does not exist "' + a_input + '"', file=sys.stderr)
else:
    # run original command
    s_cmd = [ a_cmd, a_input ]
    with open(a_output, 'w') as outfile:
        subprocess.call(s_cmd, stdout=outfile, shell=False)

    # get size
    if not os.path.isfile(a_output):
        print(sys.argv[0] + ': original output file does not exist "' + a_output + '"', file=sys.stderr)
    else:
        with open(a_output, 'r') as outfile:
            s_text = outfile.read().strip()
            s_size = len(s_text)

# check size
if s_size > 6:
    exit(0)
print(sys.argv[0] + ': original output file has a size of zero "' + a_output + '"', file=sys.stderr)

# only override custom
if 'custom' not in a_input:
    print(sys.argv[0] + ': original input file is not custom "' + a_input + '"', file=sys.stderr)
    exit(1)


# figure out which mario sound path to try to grab
m_path = 'sound/samples/sfx_mario/'
if '_peach' in a_input:
    m_path = 'sound/samples/sfx_mario_peach/'

# make sure mario path exists
if not os.path.isdir(m_path):
    print(sys.argv[0] + ': could not find override mario path "' + m_path + '" for "' + a_input + '"', file=sys.stderr)
    exit(1)

# generate table of mario sounds
m_table = {}
m_any_sound = None
for m_file in os.listdir(m_path):
     m_filename = m_path + os.path.basename(m_file)
     m_hex = m_file.split('_')[0].upper()
     m_table[m_hex] = m_filename
     m_any_sound = m_filename

# figure out input hex
n_hex = os.path.basename(a_input).split('.')[0].split('_')[0].upper()
if n_hex not in m_table:
    print(sys.argv[0] + ': could not find hex in mario table "' + m_path + '" for "' + a_input + '"', file=sys.stderr)
    n_input = m_any_sound
else:
    # override input file
    n_input = m_table[n_hex]

# run override command
s_cmd = [ a_cmd, n_input ]
with open(a_output, 'w') as outfile:
    subprocess.call(s_cmd, stdout=outfile, shell=False)

# get size
if not os.path.isfile(a_output):
    print(sys.argv[0] + ': override output file does not exist "' + a_output + '"', file=sys.stderr)
else:
    with open(a_output, 'r') as outfile:
        s_text = outfile.read().strip()
        s_size = len(s_text)

# check size
if s_size <= 0:
    print(sys.argv[0] + ': override output file has a size of zero "' + a_output + '"', file=sys.stderr)
    exit(1)
