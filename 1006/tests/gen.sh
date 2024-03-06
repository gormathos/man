#!/bin/bash

echo "01.in 4 4 10 20" | ./gen.py 
echo "02.in 1 40 12 56" | ./gen.py 
echo "03.in 50 1 3 29" | ./gen.py 
echo "04.in 20 25 11 96" | ./gen.py 
echo "05.in 50 50 6 87" | ./gen.py 
echo "06.in 60 45 8 77" | ./gen.py 
echo "07.in 45 100 10 82" | ./gen.py 
echo "08.in 100 4 10 93" | ./gen.py 
echo "09.in 99 99 10 90" | ./gen.py 
echo "10.in 100 100 2 99" | ./gen.py
for i in `seq -w 1 10`; do cat $i.in | ../sols/sol_ok.py > $i.out; done 
