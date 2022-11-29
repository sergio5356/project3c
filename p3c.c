#include <stdlib.h>
#include <stdio.h>
#include "treeADT.h"
#include "queue.h"


void displayTree(treeADT *tree);


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

	int i, *nums;

	if(argc == 1){
		fprintf(stderr, "usage: %s list of ints to insert into tree\n", argv[0]);
		return 0;
	}

	nums = malloc((argc-1) * sizeof(int));
	if(nums == NULL){
		fprintf(stderr,"error allocating space for ints\n");
		exit(1);
	}


	treeADT *myTree = initTree(myCompare);

	for(i = 1; i < argc; i++){
		nums[i-1] = atoi(argv[i]);

		insertBranch(myTree, &nums[i-1]);
		printf("after inserting %d:\n",nums[i-1]);
		displayTree(myTree);
	}


}



//the most stupid hacky display tree you'll ever see
//a line of N's prints out at the end. to make it go away
//would need a much more sophisticated solution that I don't feel
//like figuring out right now
void displayTree(treeADT *tree){
	int level = 0;
	int node_level;
	int hacky = 0;
	char c = 'N';
	node *cur;
	queue *q;
	q = init_queue();


	enqueue(q,tree->root,0);  

	while(!is_empty(q)){
		cur = dequeue(q, &node_level);

		if(cur == NULL){

			if(level < node_level && hacky == 0){
				break;
			}

			enqueue(q, NULL, node_level+1);
			enqueue(q, NULL, node_level+1);
			if(level < node_level){
				printf("\n");
				level++;
				hacky = 0;
			}
			printf("%5c", c);
			continue;
		}

		hacky = 1;

		//if(cur->left != NULL){
		enqueue(q, cur->left, node_level+1);
		//}
		//if(cur->right != NULL){
		enqueue(q, cur->right, node_level+1);
		//}

		if(level < node_level){
			printf("\n");
			level++;
		}

		printf("%5d", *(int *)cur->data);

	}

	printf("\n\n");

	while(!is_empty(q)){
		dequeue(q, &node_level);
	}


	free(q);

}
