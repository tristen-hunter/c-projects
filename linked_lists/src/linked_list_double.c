// Implementing a doublly linked list in C 

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int num;
	struct node *next;
	struct node *prev;
} node;

// Link all nodes together
node *create_linked_list(size_t size);

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
	node *tmp = NULL;
	node *tp = NULL;

	for (size_t i = 0; i < size; i++)
	{
		tmp = (node*)malloc(sizeof(node));

		if (tmp == NULL)
		{	
			printf("Memory allocation failed");
			exit(EXIT_FAILURE);
		}


		tmp->next = NULL;
		tmp->prev = NULL;

		printf("What value is stored in node %zu: ", i + 1);
		scanf("%d", &tmp->num);


		if (head == NULL)
		{
			head = tmp;
		} else
		{
			tp = head;

			while (tp->next !=NULL)
				tp = tp->next;

			tp->next = tmp;
			tmp->prev = tp;

		}
	}
	return head;
}


void print_list(node *head)
{
	node *tp = head;

	// Traverse to the end
	while (tp->next != NULL)
		tp = tp->next;

	// Reverse the list and print
	while (tp != NULL)
	{
		printf(" ------------\n");
		printf("| Data: %d\n", tp->num);
		printf("|------------\n");
		printf("| Next Node:\n");
		printf("|%p\n", tp->next);
		printf("|--------\n");
		printf("| Prev Node:\n");
		printf("|%p\n", tp->prev);
		printf(" --------\n");
		if (tp->next != NULL)
		{
						
		}
		printf("   |\n");
		printf("   |\n");
		printf("   V\n");


		tp = tp->prev;
	}
}
