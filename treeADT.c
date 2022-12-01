#include <stdlib.h>
#include <stdio.h>
#include "treeADT.h"






treeADT *initTree(int (*compare)(const void*, const void*)){
	treeADT *toReturn = malloc(sizeof(treeADT));
	if(toReturn == NULL){
		fprintf(stderr,"error allocating a tree\n");
		exit(1);
	}



	toReturn->root = NULL;

	toReturn->compare = compare;

	return toReturn;
}

node *initBranch(void *data){
	node *toReturn = malloc(sizeof(node));
	if(toReturn == NULL){
		fprintf(stderr,"error allocating a node\n");
		exit(1);
	}

	toReturn->parent = NULL;
	toReturn->left = NULL;
	toReturn->right = NULL;
	toReturn->BF = 0;
	toReturn->data = data;

	return toReturn;


}


void insertBranch(treeADT *tree, void *data){

	node *toInsert = initBranch(data);

	//if the tree is empty
	if(tree->root == NULL){
		tree->root = toInsert;
		return;
	}

	//tree is not empty, must first find 
	//location where it will be inserted
	//like a regular BST
	node *cur = tree->root;
	node *parent;
	int result;

	while(cur != NULL){
		parent = cur;
		result = tree->compare(toInsert->data, cur->data);

		if(result <= 0){
			cur = cur->left;
		}else{
			cur = cur->right;
		}
		
	}

	toInsert->parent = parent;

	if(result <= 0){
		parent->left = toInsert;
	}else{
		parent->right = toInsert;
	}


	balanceTreeInsertion(tree, toInsert);



}


static node* right_child(node *N){
	return N->right;
}

static node* left_child(node *N){
	return N->left;
}

static node* parent(node *N){
	return N->parent;
}

static int BF(node *N){
	return N->BF;
}

//Y's parent pointer is updated in the calling function
static node* rotate_RightLeft(node *X, node *Z){

	node *Y,*t3,*t2;


	// Z is by 2 higher than its sibling
	Y = left_child(Z); // Inner child of Z
			   // Y is by 1 higher than sibling
	t3 = right_child(Y);
	//left_child(Z) = t3;
	Z->left = t3;
	if (t3 != NULL){
		//parent(t3) = Z;
		t3->parent = Z;
	}
	//right_child(Y) = Z;
	Y->right = Z;
	//parent(Z) = Y;
	Z->parent = Y;
	t2 = left_child(Y);
	//right_child(X) = t2;
	X->right = t2;
	if (t2 != NULL){
		//parent(t2) = X;
		t2->parent = X;
	}
	//left_child(Y) = X;
	Y->left = X;
	//parent(X) = Y;
	X->parent = Y;
	// 1st case, BF(Y) == 0,
	//   only happens with deletion, not insertion:
	if (BF(Y) == 0) {
		//BF(X) = 0;
		X->BF = 0;
		//BF(Z) = 0;
		Z->BF = 0;
	} else{
		// other cases happen with insertion or deletion:
		if (BF(Y) > 0) { // t3 was higher
			//BF(X) = –1;  // t1 now higher
			X->BF = -1;
			//BF(Z) = 0;
			Z->BF = 0;
		} else {
			// t2 was higher
			//BF(X) = 0;
			X->BF = 0;
			//BF(Z) = +1;  // t4 now higher
			Z->BF = 1;
		}
	}
	//BF(Y) = 0;
	Y->BF = 0;
	return Y; // return new root of rotated subtree
}

//Z's parent pointer is updated in the calling function
static node* rotate_Left(node *X, node *Z){

	node *t23;


	// Z is by 2 higher than its sibling
	t23 = left_child(Z); // Inner child of Z
	//right_child(X) = t23;
	X->right = t23;
	if (t23 != NULL){
		//parent(t23) = X;
		t23->parent = X;
	}
	//left_child(Z) = X;
	Z->left = X;
	//parent(X) = Z;
	X->parent = Z;
	// 1st case, BF(Z) == 0,
	//   only happens with deletion, not insertion:
	if (BF(Z) == 0) { // t23 has been of same height as t4
		//BF(X) = +1;   // t23 now higher
		X->BF = 1;
		//BF(Z) = –1;   // t4 now lower than X
		Z->BF = -1;
	} else
	{ // 2nd case happens with insertion or deletion:
		//BF(X) = 0;
		X->BF = 0;
		//BF(Z) = 0;
		Z->BF = 0;
	}
	return Z; // return new root of rotated subtree
}

//copied rotate_RightLeft and then modified it
static node* rotate_LeftRight(node *X, node *Z){

	node *Y,*t3,*t2;


	// Z is by 2 higher than its sibling
	Y = right_child(Z); // Inner child of Z
			   // Y is by 1 higher than sibling
	t3 = left_child(Y);
	//left_child(Z) = t3;
	Z->right = t3;
	if (t3 != NULL){
		//parent(t3) = Z;
		t3->parent = Z;
	}
	//right_child(Y) = Z;
	Y->left = Z;
	//parent(Z) = Y;
	Z->parent = Y;
	t2 = right_child(Y);
	//right_child(X) = t2;
	X->left = t2;
	if (t2 != NULL){
		//parent(t2) = X;
		t2->parent = X;
	}
	//left_child(Y) = X;
	Y->right = X;
	//parent(X) = Y;
	X->parent = Y;
	// 1st case, BF(Y) == 0,
	//   only happens with deletion, not insertion:
	if (BF(Y) == 0) {
		//BF(X) = 0;
		X->BF = 0;
		//BF(Z) = 0;
		Z->BF = 0;
	} else{
		// other cases happen with insertion or deletion:
		if (BF(Y) > 0) { // t3 was higher
			//BF(X) = –1;  // t1 now higher
			X->BF = -1;
			//BF(Z) = 0;
			Z->BF = 0;
		} else {
			// t2 was higher
			//BF(X) = 0;
			X->BF = 0;
			//BF(Z) = +1;  // t4 now higher
			Z->BF = 1;
		}
	}
	//BF(Y) = 0;
	Y->BF = 0;
	return Y; // return new root of rotated subtree

}

//copied and changed rotate_Left()
static node* rotate_Right(node *X, node *Z){

	node *t23;


	// Z is by 2 higher than its sibling
	t23 = right_child(Z); // Inner child of Z
	//right_child(X) = t23;
	X->left = t23;
	if (t23 != NULL){
		//parent(t23) = X;
		t23->parent = X;
	}
	//left_child(Z) = X;
	Z->right = X;
	//parent(X) = Z;
	X->parent = Z;
	// 1st case, BF(Z) == 0,
	//   only happens with deletion, not insertion:
	if (BF(Z) == 0) { // t23 has been of same height as t4
		//BF(X) = +1;   // t23 now higher
		X->BF = 1;
		//BF(Z) = –1;   // t4 now lower than X
		Z->BF = -1;
	} else
	{ // 2nd case happens with insertion or deletion:
		//BF(X) = 0;
		X->BF = 0;
		//BF(Z) = 0;
		Z->BF = 0;
	}
	return Z; // return new root of rotated subtree

}

//I'm not going to write this function from scratch.
//I stole this from wikipedia, and I don't care
void balanceTreeInsertion(treeADT *tree, node *inserted){



	node *Z = inserted;
	node *X,*G,*N;


	for (X = parent(Z); X != NULL; X = parent(Z)) { // Loop (possibly up to the root)
							// BF(X) has to be updated:
		if (Z == right_child(X)) { // The right subtree increases
			if (BF(X) > 0) { // X is right-heavy
					 // ==> the temporary BF(X) == +2
					 // ==> rebalancing is required.
				G = parent(X); // Save parent of X around rotations
				if (BF(Z) < 0){                  // Right Left Case  (see figure 3)
					N = rotate_RightLeft(X, Z); // Double rotation: Right(Z) then Left(X)
				}
				else{                            // Right Right Case (see figure 2)
					N = rotate_Left(X, Z);      // Single rotation Left(X)
				}
				// After rotation adapt parent link
			} else {
				if (BF(X) < 0) {
					//BF(X) = 0; // Z’s height increase is absorbed at X.
					X->BF = 0;
					break; // Leave the loop
				}
				//BF(X) = +1;
				X->BF = 1;
				Z = X; // Height(Z) increases by 1
				continue;
			}
		} else { // Z == left_child(X): the left subtree increases
			if (BF(X) < 0) { // X is left-heavy
					 // ==> the temporary BF(X) == -2
					 // ==> rebalancing is required.
				G = parent(X); // Save parent of X around rotations
				if (BF(Z) > 0){                  // Left Right Case
					N = rotate_LeftRight(X, Z); // Double rotation: Left(Z) then Right(X)
				}
				else{                            // Left Left Case
					N = rotate_Right(X, Z);     // Single rotation Right(X)
				}
								    // After rotation adapt parent link
			} else {
				if (BF(X) > 0) {
					//BF(X) = 0; // Z’s height increase is absorbed at X.
					X->BF = 0;
					break; // Leave the loop
				}
				//BF(X) = -1;
				X->BF = -1;
				Z = X; // Height(Z) increases by 1
				continue;
			}
		}

		// After a rotation adapt parent link:
		// N is the new root of the rotated subtree
		// Height does not change: Height(N) == old Height(X)

		//parent(N) = G;
		N->parent = G;
		if (G != NULL) {
			if (X == left_child(G)){
				//left_child(G) = N;
				G->left = N;
			}
			else{
				//right_child(G) = N;
				G->right = N;
			}
		} else{
			tree->root = N; // N is the new root of the total tree
		}
		break;
		// There is no fall thru, only break; or continue;
	}
	// Unless loop is left via break, the height of the total tree increases by 1.

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
