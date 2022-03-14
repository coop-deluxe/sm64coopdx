#!/usr/bin/env python3
import os

copy_directories = {
    'sound/samples/sfx_mario/': [
        'sound/samples/sfx_custom_luigi/',
        'sound/samples/sfx_custom_wario/',
    ],
    'sound/samples/sfx_mario_peach/': [
        'sound/samples/sfx_custom_luigi_peach/',
        'sound/samples/sfx_custom_wario_peach/',
    ],
}

def copy_dir(source, destinations):
    for filename in os.listdir(source):
        if not filename.endswith('.aiff'):
            continue
        src = source + filename

        shortened_name = filename.split('_')[0] + '.aiff'
        for destination in destinations:
            dst = destination + shortened_name
            if os.path.exists(dst):
                continue
            print('Copying mario sounds to character sounds: ' + src + ' -> ' + dst)
            os.system('cp ' +  src + ' ' + dst)

def main():
    for source in copy_directories:
        copy_dir(source, copy_directories[source])

if __name__ == "__main__":
    main()
