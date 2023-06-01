#!/bin/bash

#Download
echo Downloading: libjuice
dl_ver=1.2.2
curl -L https://github.com/paullouisageneau/libjuice/archive/refs/tags/v"$dl_ver".tar.gz -o libjuice.tar.gz
tar -xf libjuice.tar.gz

#Compilation
echo '
Compiling: libjuice'
cd libjuice-"$dl_ver"
cmake -B build && cd build
make -j2

#Copy to lib/coopnet/mac/libjuice.dylib
echo "
Copying: libjuice to 'lib/coopnet/mac'"
cp libjuice."$dl_ver".dylib ../../lib/coopnet/mac/libjuice."$dl_ver".dylib

echo Done
