#include <stdlib.h>
#include <stdio.h>
#include "treeADT.h"






treeADT *initTree(int (*compare)(const void*, const void*)){
	treeADT *toReturn = malloc(sizeof(treeADT));
	if(toReturn == NULL){
		fprintf(stderr,"error allocating tree\n");
		exit(1);
	}

	toReturn->root = NULL;

	toReturn->compare = compare;
}


void test(treeADT *tree, const void *p1, const void *p2){
	int result = tree->compare(p1,p2);

	if(result == -1){
		printf("p1 less than p2\n");
	}else if(result == 0){

		printf("p1 equal to p2\n");
	}else{
		printf("p1 greater than p2\n");
	}

}
