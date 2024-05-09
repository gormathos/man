
./gen01 5 01.09.2023 10:00:00 > ../tests/01.in
cat ../tests/01.in | ../sols/sol > ../tests/01.out

for i in `seq -w 2 21`; do
  ./gen $i > ../tests/$i.in
  cat ../tests/$i.in | ../sols/sol > ../tests/$i.out
done
