#!/usr/bin/env bash
python3 ./autogen/convert_structs.py $1
python3 ./autogen/convert_functions.py $1
python3 ./autogen/convert_constants.py $1
python3 ./autogen/display_lists.py $1
