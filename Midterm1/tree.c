
/*Name: Jared Shimabukuro
 * UH ID: 2257-2949
 */

/*
 *  This program will will input a full binary tree, where
 *  each leaf is a negative number, and internal nodes are
 *  positive numbers.
 *
 *  The tree is in a file and formatted as a pre-order list. 
 *  The program will input the list and store it in a linked list.
 *
 *  Then it will call create_tree() to store the input as a
 *  binary tree.
 *
 *  Then it will display the tree. 
 *
 */
#include <stdio.h>
#include <stdlib.h>


struct list_node {
	int value;
	struct list_node *next;
};

struct tree_node {
	int value;
	struct tree_node *left; /* Left child */
	struct tree_node *right; /* Right child */
};

void tree_delete(struct tree_node *node);
void list_delete(struct list_node *list);
void tree_display(struct tree_node *node);
void create_tree(struct tree_node **tree, struct list_node *list);
void create_tree_node(struct tree_node **tree, struct list_node **p);
void create_tree_node_right(struct tree_node **tree, struct list_node **p);

void main(int argc, char *argv[])
{

if (argc != 2) {
	printf("Usage:  ./a.out  <data file>\n");
	return;
}

FILE *fp;

fp = fopen(argv[1], "r");

struct list_node *in_list;
struct list_node **p;
struct list_node *node;
int value;

p = &in_list;
while(fscanf(fp, "%d", &value)==1) {
	/* Create node */
	node = (struct list_node *) malloc(sizeof(struct list_node));
	node->value = value;
	node->next = NULL;
	/* Attach node to the end of the list */
	*p = node;
	p = &(node->next);
}
fclose(fp);

struct tree_node *tree;

tree = NULL; /* Initialize tree to an empty tree */
create_tree(&tree, in_list);

tree_display(tree);

list_delete(in_list);
tree_delete(tree);
}


/*
 * You implement this.  It should create a full binary tree
 * specified by the pre-order list.  A reference to the tree is "tree"
 * and a reference to the pre-ordered list is "list" 
 */
void create_tree(struct tree_node **tree, struct list_node *list)
{
	create_tree_node(tree, &list);
	create_tree_node_right(tree, &list);

	tree = &((*tree)->right);
	create_tree_node(tree, &list);
	printf("\n");
}

void create_tree_node(struct tree_node **tree, struct list_node **p){
	struct tree_node *temp;
	struct tree_node **tempTree = tree;
	temp = (struct tree_node *) malloc(sizeof(struct tree_node));

	temp->value = (*p)->value;
	*p = (*p)->next;
	printf("Inserting Node %d...\n", temp->value);
	*tempTree = temp;

	if((*tempTree)->value >= 0){
		tempTree = &((*tempTree)->left);
		create_tree_node(tempTree, &(*p));
	}
	
}

void create_tree_node_right(struct tree_node **tree, struct list_node **p){
        struct tree_node **temp = tree;
        while((*temp)->left->value >= 0){
                temp = &((*temp)->left);
        }
        temp = &((*temp)->right);
	if((*temp)->value >= 0){
        	create_tree_node(temp, &(*p));
		temp = &((*temp)->right);
		create_tree_node(temp, &(*p));
	}
}

/* Display the tree */
void tree_display(struct tree_node *node)
{
if (node == NULL) return;
if (node->value < 0) {
	printf("Tree node %d is a leaf\n", node->value);
}
else {
	printf("Tree node %d children: left = %d, right = %d\n",
			node->value,
			(node->left)->value,
			(node->right)->value);
	tree_display(node->left);
	tree_display(node->right);
}
}

/* Deletes the linked list */
void list_delete(struct list_node *list)
{
struct list_node *p;
struct list_node *temp;

p = list;
while (p != NULL) {
	temp = p;
	p = p->next;
	free(temp);
}
}

/* Deletess the tree */
void tree_delete(struct tree_node *node)
{
if (node==NULL) return;
if (node->value >= 0) {
	tree_delete(node->left);
	tree_delete(node->right);
	free(node);
}
else {
	free(node);
}

}
