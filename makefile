out.exe: p3c.o treeADT.o
	gcc -o out.exe p3c.o treeADT.o

p3c.o: p3c.c treeADT.h
	gcc -c -o p3c.o p3c.c

treeADT.o: treeADT.c treeADT.h
	gcc -c -o treeADT.o treeADT.c
