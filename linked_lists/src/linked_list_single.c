// Singly Linked List Implementation in C

#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
	int num;
	struct node *next;
}node;

// Function for creating the linked list
node *create_linked_list(size_t size); // creates size nodes and returns the head node

// Print the linked list
void print_list(node *head);


int main(void) {

	size_t size;

	node *HEAD = NULL;

	printf("Enter the size of the linked list: ");
	scanf("%zu", &size);

	printf("You chose %zu\n Creating List:\n", size);

	HEAD = create_linked_list(size);

	print_list(HEAD);

	return 0;
}


node *create_linked_list(size_t size)
{
	
	node *head = NULL;
	node *temp = NULL;
	node *p = NULL;

	for (size_t i = 0; i < size; i++)
	{
		temp = (node*)malloc(sizeof(node));

		temp->next = NULL;

		printf("What value is stored in node %zu: ", i + 1);
		scanf("%d", &(temp->num));

		if (head == NULL) {
			 head = temp;
		} else 
		{
			p = head;

			while (p->next != NULL)
				p = p->next;

			p->next = temp;
		}
	}
	return head;
}


void print_list(node *head)
{
	node *tp = head;

	while (tp != NULL)
	{
		printf("-------------\n");
		printf("| Data: %d\n", tp->num);
		printf("|------------\n");
		printf("| Next Node:\n");
		printf("|%p\n", tp->next);
		printf("---------\n");
		printf("   |\n");
		printf("   |\n");
		printf("   V\n");

		tp = tp->next;
	}
}
