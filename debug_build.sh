#!/bin/bash
set -e # use -e to abort when anything goes wrong

#run ctags if present
[[ -f `which ctags` ]] && ctags --extra=+f --fields=+l -R . &

sweb_dir=$(pwd)
mkdir -p /tmp/sweb
cd /tmp/sweb

# Uncomment to generate compile_commands.json
echo "building debug sweb"
cmake -DDEBUG=1 "$sweb_dir"
# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DDEBUG=1 "$sweb_dir"
make -j4
make qemugdb

# cp compile_commands.json "$sweb_dir"
