import os
import subprocess

def bash(args):
    return subprocess.run(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True, text=True).stdout

directory = './sound/samples/sfx_custom_wario_peach/'
for filename in os.listdir(directory):
    f = os.path.join(directory, filename)
    if f.split('.')[-1] != 'aiff':
        continue

    cmd = ['ffprobe', '-i', f, '-show_entries', 'format=duration', '-v', 'quiet']
    result = bash(cmd)
    result = result.split('duration=')[-1].split('\n')[0].strip()
    seconds = float(result)
    hundredths = int(seconds * 100)

    fname = filename.split('.')[0]

    print(str(int(fname, 16)).ljust(4) + " : " + hex(hundredths))

# ffprobe -i ./sound/samples/sfx_custom_wario/00.aiff -show_entries format=duration -v quiet -of csv="p=0"
#print(bash('ffprobe -i ./sound/samples/sfx_custom_wario/00.aiff -show_entries format=duration -v quiet -of csv="p=0"'))