#!/usr/bin/env python3
import os, shutil

copy_directories = [
    'sound/samples/instruments/',
    'sound/samples/bowser_organ/',
    'sound/samples/course_start/',
    'sound/samples/piranha_music_box/'
]

destination = 'sound/samples/extended/'

def main():
    for source in copy_directories:
        if not os.path.exists(source):
            continue

        shutil.copytree(source, destination, dirs_exist_ok=True)
        print('copying to extended sample bank', source)

if __name__ == "__main__":
    main()
