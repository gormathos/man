#!/bin/bash

arch=$1
name=`echo $arch | awk -F"." '{print $1}'`
tar xfpz $1

sol=$2

run_ddots --problem-root $name --solution-filepath ./$2 | grep Test

rm -rf $name
