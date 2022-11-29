out.exe: p3c.o treeADT.o queue.o
	gcc -o out.exe p3c.o treeADT.o queue.o

p3c.o: p3c.c treeADT.h queue.h
	gcc -c -o p3c.o p3c.c

treeADT.o: treeADT.c treeADT.h
	gcc -c -o treeADT.o treeADT.c

queue.o: queue.c queue.h
	gcc -c -o queue.o queue.c
