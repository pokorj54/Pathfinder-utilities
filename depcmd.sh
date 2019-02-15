#!/bin/bash
rm tmp.txt

for file in ./src/*/*.cpp ./src/*.cpp
do
	printf "bin/" >>tmp.txt
	gcc -std=c++11 -MM $file | tr -d '\n' | sed 's: \\::g'| sed 's:/[a-zA-Z]*/../:/:g'| sed 's:/[a-zA-Z]*/../:/:g'| sed 's:/[a-zA-Z]*/../:/:g' >>tmp.txt
	echo "" >> tmp.txt
	echo "" >> tmp.txt
done
