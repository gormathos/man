for i in `seq -w 1 10`; do cp ../tests/$i.in input.npz; ./sol.py > output.txt; ../checker/check input.npz ../tests/$i.out output.txt; done
