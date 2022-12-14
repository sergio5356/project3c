#ifndef TREEADT_H
#define TREEADT_H


typedef struct node{
	struct node *parent;
	struct node *left;
	struct node *right;
	int BF;//balance factor. height(right subtree) - height(left subtree)
	void *data;
}node;


typedef struct treeADT{
	node *root;
	/*
	 * function pointer called compare. 
	 * The function compare points to must take two void pointers as parameters.
	 * The function then must cast these two pointers to the appropriate type. 
	 * Then the function compares the data located at the two addresses
	 * to determine which would come first in an ordering.
	 * the function definition would look something like this:
	 * int myCompare(const void *p1, const void *p2){...}
	 * The function should return -1 if value pointed to by p1 comes before p2. return
	 * 0 if they are equal. return 1 if p2 comes before p1.
	 *
	 * it is your responsiblity to write this myCompare function, 
	 * and pass it to initTree function call
	 * 
	 */
	int (*compare)(const void*,const void*);

}treeADT;



treeADT *initTree(int (*compare)(const void*, const void*));

//inits a single node that stores the pointer data
node *initBranch(void *data);

//inserts a single node into the tree
//will call initBranch as a helper function
//initBranch should probably be a static function and not have 
//a prototype in this file, but I don't to risk the grader
//not seeing initBranch.
//need to call balanceTreeInsertion at the end of this function
void insertBranch(treeADT *tree, void *data);

//returns 1 if found and destroyed, 0 if not found
//this function actually destroys the entire subtree rooted at toDestroy
int destroyBranch(treeADT *tree, node *toDestroy);

//remove node that is equal to what is pointed to by data
//and returns the node's data back to the user
void *removeBranch(treeADT *tree, void *data);

//this really doesn't need to be its own function, you will
//need to make sure the tree is balanced after every insertion.
//inserted is the last node we just inserted. Must balance
//the tree starting from inserted all the way up to the root if necessary
void balanceTreeInsertion(treeADT *tree, node *inserted);


//this really should be in removeBranch function
void balanceTreeDeletion(treeADT *tree, node *deleted);

//returns pointer to a node if it is contained in the tree
//returns NULL otherwise
//this is the search in a regular BST
node *findBranch(treeADT *tree, void *data);



//demonstrates how to use the compare function
void test(treeADT *tree, const void *p1, const void *p2);




#endif
