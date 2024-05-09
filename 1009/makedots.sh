#!/bin/bash

#  if [ -z $@ ]
#    then
#      echo "Надо указать язык, на котором подготовлено условие задачи"
#      echo "Надо доделать многоязыковую поддержку!"
#      exit
#  fi

  fin=`cat statements/problem.tex | sed -n '1p' | awk -F} '{print $3}' | sed -e 's/{//'`
  if [ -z $fin ]
    then fin=stdin
  fi
  fout=`cat statements/problem.tex | sed -n '1p' | awk -F} '{print $4}' | sed -e 's/{//'`
  if [ -z $fout ]
    then fout=stdout
  fi
  tl=`cat statements/problem.tex | sed -n '1p' | awk -F} '{print $5}' | sed -e 's/{//' | awk '{print $1}'`
  ml=`cat statements/problem.tex | sed -n '1p' | awk -F} '{print $6}' | sed -e 's/{//' | awk '{print $1}'`
  title=`cat statements/problem.tex | sed -n '2p' | sed -e 's/% //g'`
  

  ini=task.ini
  > $ini
  echo "[PROBLEM]" >> $ini
  echo -n "LANG=" >> $ini
  for i in `echo $@`
  do
    echo -n "$i " >> $ini
  done
  echo >> $ini
  echo "TITLE=$title" >> $ini
  echo "FIN=$fin" >> $ini
  echo "FOUT=$fout" >> $ini
  echo "TL=$tl" >> $ini
  echo "ML=$ml" >> $ini
  echo "[TESTS]" >> $ini
  
  numtests=`ls tests/*in | wc -l`
  echo "numtests=$numtests" >> $ini 
  ball=`echo "scale = 1; 96 / $numtests" | bc -l`
#  ball=$(printf "%.1f" $ball)

  if [ -f tests/SCORE ]
  then
    cat tests/SCORE >> $ini
  else
    for q in `seq -w 1 $numtests`
    do
      echo "T$q=$ball" >> $ini
    done
  fi
  
  echo "[DESCRIPTION]" >> $ini
  echo "#problem" >> $ini
  echo "<attachment>" >> $ini


  arch=$(basename `pwd`)
  mkdir $arch
  mkdir $arch/files

## GEN PROBLEM.XML #######################################################
  xml="$arch/Problem.xml"
  > $xml
  echo "<?xml version=\"1.0\" encoding=\"windows-1251\"?>
<!-- Problem exchange format 0.1 -->
<Problem
   TimeLimit=\"$tl\"
   MemoryLimit=\"$ml\"
   InputFile=\"$fin\"
   OutputFile=\"$fout\"
   CheckerExe=\"check\"
   TestCount=\"$numtests\"
   PointsOnGold=\"100\">" >> $xml
   let tn=0
   for i in `grep "T[0-9]" $ini | awk -F= '{print $2}'`
   do
     if [ $numtests -lt 10 ]
     then
       let tn+=1
       echo "<Test Input=\"$tn.in\" Answer=\"$tn.out\" Points=\"$i\"/>" >> $xml
       
     else 
     if [ $numtests -lt 100 ]
     then
       let tn+=1
       if [ $tn -lt 10 ]
       then
         echo "<Test Input=\"0$tn.in\" Answer=\"0$tn.out\" Points=\"$i\"/>" >> $xml
       else
         echo "<Test Input=\"$tn.in\" Answer=\"$tn.out\" Points=\"$i\"/>" >> $xml
       fi
     else
       let tn+=1
       if [ $tn -lt 10 ]
       then
         echo "<Test Input=\"00$tn.in\" Answer=\"00$tn.out\" Points=\"$i\"/>" >> $xml
       else
         if [ $tn -lt 100 ]
         then
           echo "<Test Input=\"0$tn.in\" Answer=\"0$tn.out\" Points=\"$i\"/>" >> $xml
         else
           echo "<Test Input=\"$tn.in\" Answer=\"$tn.out\" Points=\"$i\"/>" >> $xml
         fi
       fi
     fi
     fi 
  done
  echo "</Problem>" >> $xml



  cp tests/*in tests/*out checker/check $arch
  cp -r sols checker gentests statements $arch/files/
  cp *sh complexity $arch/files/
  
  if [ -f $arch.config ]
    then
       cp $arch.config $arch/files/problem.config
       sed -i 's/^.*Gold.*$/>/' $arch/Problem.xml
  fi
  tar cfpz  $arch.tar.gz $arch/ 

  rm -rf task.ini $arch
