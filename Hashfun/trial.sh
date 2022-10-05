#!/bin/bash
input=("1_1.in" "1_2.in" "1_3.in" "2_1.in" "2_2.in" "2_3.in")
args=("1" "2" "3")
rm "time.txt"
for i in ${input[@]}
do 
	for a in ${args[@]}
	do 
		for b in ${args[@]}
		do
			./main.exe $i ${i1:4}"out" $a $b
			# echo $i $a $b \n
		done
	done 	
done 