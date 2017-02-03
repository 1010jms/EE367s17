/*
 * Fill in your name here:  Jared Shimabukuro
 *
 * This program will store words in a singly linked list.
 * It allows the user to append, delete, list, rotate, etc.
 * Rotate is not implemented. 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Definitions

struct ListNode {
   char              word[100];
   struct ListNode * next;
   }; 

struct LinkedList {
   struct ListNode * head; // Head which points to first element in list
   };

// Function prototypes
char get_command();
void init_list(struct LinkedList *list);
void append_list(struct LinkedList *list);
void display_list(struct LinkedList *list);
void delete1(struct LinkedList *list);
void rotate_list(struct LinkedList *list);
void rotate(struct LinkedList *list, int n);
void help();

int main()
{
char command;
struct LinkedList list;

init_list(&list);

do {
  command = get_command();
  switch(command) {
     case 'a': append_list(&list);
               break;
     case 'd': delete1(&list);
               break;
     case 'l': display_list(&list);
               break;
     case 'r': rotate_list(&list);
               break;
     case 'h': help();
               break;
     case 'e': printf("Exiting program\n");
     } 

  } while(command!='e');
}

// 
//  The following function calls another function "rotate" to 
//  do the rotation.  
//
void rotate_list(struct LinkedList *list)
{
int shift;

printf("Enter the number of positions to shift: "); 
scanf("%d", &shift);
rotate(list, shift);
}

//
// Implement the following function that rotates the linked list
// to the right by n positions
//

void rotate(struct LinkedList *list, int n)
{

	struct ListNode ** current_ref;
	struct ListNode * temp;
	struct ListNode * temp2;

	for(int count = 0; count < n; count++){
		current_ref = &(list->head);

		while((*current_ref)->next != NULL){
			current_ref = &((*current_ref)->next);
		}

		temp = *current_ref;
		current_ref = &(list->head);
		temp->next = (*current_ref)->next;

		while((*current_ref)->next != list->head){
			printf("%s", (*current_ref)->word);
			temp2 = *current_ref;
			printf("%s",temp2->word);
			*current_ref = temp;
			printf("%s",(*current_ref)->word); 
			temp = temp2;
			printf("%s",temp->word);
			current_ref = &((*current_ref)->next);
			printf("%s",(*current_ref)->next);
			printf("\n");
		}

		(*current_ref)->next = NULL;
	}
}



void delete1(struct LinkedList *list)
{
struct ListNode ** current_ref;
struct ListNode target;         // Stores the word to delete
struct ListNode * temp;

current_ref = &(list->head);    // current_ref points to "head" of list.

// Get the word to delete 
printf("Enter word to delete: ");
scanf("%s",target.word);
while(getchar() != '\n');   // Get rid of spurious characters entered

while (*current_ref != NULL) {
   if (strcmp((*current_ref)->word,target.word) == 0) break;
   current_ref = &((*current_ref)->next);
}

// The following deletes the node (if there one to delete)
if (*current_ref != NULL) {
   temp = *current_ref;
   *current_ref = (*current_ref)->next;
   free(temp);                            // Good housekeeping
}
else printf("[%s] is not in the list\n",target.word);
}

void init_list(struct LinkedList *list)
{
list->head = NULL;
}

void append_list(struct LinkedList *list)
{
int i;
int result;
struct ListNode * newentryptr;
struct ListNode ** lastptr;

newentryptr = (struct ListNode *) malloc(sizeof(struct ListNode));

if (newentryptr == NULL) {
   printf("Can't add to list, memory's full\n");
   return;
   }

// Initialize the new entry by getting a word  from the user
// and making the next pointer equal NULL

printf("Enter new word: ");
scanf("%s",newentryptr->word);
while(getchar() != '\n') {}   // Get rid of spurious characters entered
                              //  by the user
newentryptr->next = NULL; 

// Find the end of the linked list then append the new node.
lastptr = &(list->head); // Initializes lastptr to point to head
while (* lastptr != NULL) {  // Stop if you're at the end
   lastptr = &((*lastptr)->next); // lastptr is updated so it points to
                               // the next node's "next" member.
}  
// Now we add the new entry

* lastptr = newentryptr;

printf("Added '%s' to the list\n",newentryptr->word);
}

void display_list(struct LinkedList *list)
{
struct ListNode * node_ptr;

node_ptr = list->head;

if (node_ptr == NULL) {
   printf("List is empty\n");
   return;
   }

while (node_ptr != NULL) {
   printf("%s\n",node_ptr->word);
   node_ptr = node_ptr->next;
}

}

char get_command( )
{
char command;
int  valid;

do {
   printf("\nEnter command a(dd) d(elete) l(ist) h(help) r(otate) or e(xit): ");
   command = getchar();
   while(getchar() != '\n') { } // Get rid of spurious characters
   switch(command){
      case 'a':
      case 'd':
      case 'e':
      case 'h':
      case 'r':
      case 'l': valid = 1;
                break;
      default:  valid = 0;
                printf("Your entry '%c' is invalid!\n",command);
      }
   } while(valid == 0);

return(command);
}

void help()
{
printf("\nDescription of commands\n");
printf("   a:  Append a word to the list\n");
printf("   d:  Delete a word from the list\n");
printf("   D:  Delete the second to the last word the list\n");
printf("   l:  List the list\n");
printf("   r:  Rotate the linked list\n");
printf("   e:  Exit the program\n");
printf("\n");
}

