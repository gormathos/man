#!/bin/bash

N=$(find . -maxdepth 1 -type f -name "*.in" | wc -l)

for i in $(seq -w 1 $N); do
    if [ "$i" -lt 11 ]; then
        echo "File: $i.in"
        cat "$i.in"
        echo ""

        echo "File: $i.out"
        cat "$i.out"
        echo ""

        echo "=================================================="
    else
        echo "File: $i.out"
        cat "$i.out"
        echo ""

        echo "=================================================="
    fi
done
