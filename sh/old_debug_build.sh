#!/bin/bash
set -e

# One step script that compiles sweb in debug mode and launches
# the debugger in a second terminal
# Deprecated for recent sweb

time_delay=5 # hit the enter key in qemu launch menu quickly


# Use cgdb as debugger, does not really work for x86_64
helper_script="helper_script.sh"
echo -e '#!/bin/bash\n make runcgdb' > $helper_script
chmod +x $helper_script
cwd=$(pwd)

mkdir -p /tmp/sweb
cd /tmp/sweb
cmake "$cwd"
make debug
make qemugdb &! (sleep $time_delay && x-terminal-emulator -e $cwd/$helper_script)
rm $cwd/$helper_script
