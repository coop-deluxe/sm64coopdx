#!/bin/bash
dl_ver=1.2.2

#Download
echo Downloading: libjuice
curl -L https://github.com/paullouisageneau/libjuice/archive/refs/tags/v"$dl_ver".tar.gz -o libjuice.tar.gz
tar -xf libjuice.tar.gz

#Compilation
echo '
Compiling: libjuice'
cd libjuice-"$dl_ver"
cmake -B build && cd build
make -j2

#Copy to ../../lib/coopnet/mac_intel/libjuice.1.2.2.dylib
echo "
Copying: libjuice to 'lib/coopnet/mac_intel/'"
cp libjuice."$dl_ver".dylib ../../lib/coopnet/mac_intel/libjuice."$dl_ver".dylib

echo Done
