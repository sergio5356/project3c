#include <stdio.h>
#include "treeADT.h"



int myCompare(const void *p1, const void *p2){
	if( *(int*)p1 < *(int*)p2){
		return -1;
	}else if( *(int*)p1 == *(int*)p2){
		return 0;
	}else{
		return 1;
	}
}


int main(int argc, char *argv[]){
	treeADT *myTree = initTree(myCompare);

	int x = 80;
	int y = 80;

	test(myTree, &x, &y);

}
