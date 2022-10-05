all: AVL.cpp Splay.cpp
	g++ AVL.cpp -o AVL
	./AVL
	g++ Splay.cpp -o Splay
	./Splay
avltest: avldata test
splaytest: splaydata test 
test: AVL.exe Splay.exe
	./AVL
	./Splay
test0: makedata.exe AVL.exe Splay.exe
	./makedata 0
	./AVL
	./Splay
test1: makedata.exe AVL.exe Splay.exe
	./makedata 1
	./AVL
	./Splay	
avldata: makedata.cpp 
	g++ makedata.cpp -o makedata
	./makedata 0
splaydata: makedata.cpp 
	g++ makedata.cpp -o makedata
	./makedata 1

