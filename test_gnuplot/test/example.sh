#!/bin/bash
#
g++ -c -I/$HOME/include example.cpp
if [ $? -ne 0 ]; then
  echo "Errors compiling example.cpp"
  exit
fi
#
g++ example.o gnuplot_i.o
if [ $? -ne 0 ]; then
  echo "Errors linking and loading example.o"
  exit
fi
rm example.o
#
#mv a.out ~/bincpp/$ARCH/example
#
echo "Executable installed as ~/bincpp/$ARCH/example"

