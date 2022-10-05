all: main
hashtable:
	g++ hashtable.cpp -o hashtable.o -c
main: hashtable
	g++ main.cpp hashtable.o -o main	
test: 	
	g++ -g main.cpp hashtable.o -o test
data:
	g++ makedata.cpp -o makedata	
	.\makedata 1 4000 20000 > 1_1.in
	.\makedata 1 12000 12000 > 1_2.in 
	.\makedata 1 20000 4000 > 1_3.in  
	.\makedata 2 4000 20000 > 2_1.in
	.\makedata 2 12000 12000 > 2_2.in 
	.\makedata 2 20000 4000 > 2_3.in

	