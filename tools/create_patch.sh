#!/bin/sh
#
# create_patch.sh - Creates an enhancement patch based on the current Git changes
#

if [ "$#" -ne 1 ]
then
    echo "Usage: $0 patch_file"
    echo '    Creates a patch file based on the changes made to the current directory'
    exit 1
fi

# 'git diff' is stupid and doesn't show new untracked files, so we must add them first.
# Also make sure this is a valid git repository, throw an error otherwise ( || exit 1 )
git add . || exit 1
# Generate the patch.
git diff -p --staged > "$1"
# Undo the 'git add'. 
git reset
