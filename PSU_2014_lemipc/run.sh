#!/bin/bash

if [ "$#" -ne 1 ] || [ "$1" -lt 1 ]; then
    echo -e "Usage :\n\t./run.sh [positive player amount]"
    exit 1
fi

make re

# run gui
./gui_lemipc&

./lemipc&
sleep 1

# run players
for num in `seq 2 "$1"`
do
    ./lemipc&
    usleep 100
done
