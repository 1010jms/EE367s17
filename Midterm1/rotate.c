
/* Name: Jared Shimabukuro
 * UH ID: 2257-2949
 */

/*
 *  This program will rotate a linked list to the rright.
 *  The data file is formatted as follows
 *
 *  5  3
 *  1
 *  2
 *  5
 *  4
 *  3
 *
 *  The line indicates the size of the list and the amount to
 *  shift.  In this example, the linked list has 5 nodes,
 *  and is to be shifted by 3 nodes.
 *  The next lines are the node values 
 *
 *  Thus, the initially (before rotation), the linked list is
 *
 *  1 -> 2 -> 5 -> 4 ->3 -> /
 *
 *  After the right rotation, the linked list will be
 *
 *  5 -> 4 -> 3 -> 1 -> 2 -> /
 *
 */
#include <stdio.h>
#include <stdlib.h>


struct node {
	int value;
	struct node *next;
};

void list_display(struct node *list);
void rotate_right(struct node **list, int k);
void list_delete(struct node *list);


void main(int argc, char *argv[])
{

	struct node *list;
	int list_size;
	int shift_amt; 
	FILE *fp;
	int value;
	struct node *node;
	int i;
	struct node **p;

	if (argc != 2) {
		printf("Usage:  ./a.out  <data file>\n");
		return;
	}

	fp = fopen(argv[1], "r");
	fscanf(fp, "%d %d", &list_size, &shift_amt);

	if (list_size <= shift_amt) {
		printf("Shift amount %d must be smaller than list size %d\n",
				shift_amt, list_size);
		fclose(fp);
		return;
	}

	p = &list;
	for (i = 0; i < list_size; i++) {
		fscanf(fp, "%d", &value);
		node = (struct node *) malloc(sizeof(struct node));
		node->value = value;
		node->next = NULL;
		*p = node;
		p = &(node->next);
	}

	fclose(fp);


	list_display(list);

	rotate_right(&list, shift_amt);

	list_display(list);

	list_delete(list);

}


void rotate_right(struct node **list, int k)
{
	//Calculate Size of List
	int n = 0;
	struct node *counter = *list;
	while(counter != NULL){
		n++;
		counter = counter->next;
	}

	//Find the New Starting Point After List Rotation Along with Any Nodes Following the New Starting Point
	struct node *p = *list;
	for(int count = 0; count < (n-k); count++){
		p = p->next;
	}

	//Set New Starting Point and Return Values Back Into the List in the Proper Order
	struct node **temp;
	temp = &p;
	for(int count = 0; count < k; count++){
		temp = &((*temp)->next);
	}

	*temp = *list;
	*list = p;

	//Ensure the List Ends With a NULL Value
	struct node **temp2 = &(*list);
	for(int i = 1; i < n; i++) {
		temp2 = &((*temp2)->next);
	}	
	(*temp2)->next = NULL; 
	
}


void list_display(struct node *list)
{
	struct node *p;

	printf("Linked list: ");
	for (p = list; p != NULL; p = p->next) {
		printf(" %d ->", p->value);
	}
	printf(" /\n");

}

void list_delete(struct node *list)
{
	struct node *p;
	struct node *temp;

	p = list;
	while (p != NULL) {
		temp = p;
		p = p->next;
		free(temp);
	}
}

