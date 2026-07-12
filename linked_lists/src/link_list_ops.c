//==============================
//      Linked List Manager
//==============================

// 1. Create a new list
	// free existing list (if there is)
	// ask for size and seed values
// 2. Print list (forward)
// 3. Print list (backward)
// 4. Append node
// 5. Insert node at position
// 6. Delete node by value
// 0. Exit

// Choice:

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int num;
	struct Node *next;
	struct Node *prev;
} Node;


// Function declarations
Node *create_list(size_t size);

void print_list_forw(Node *head);

void print_list_back(Node *head);

void append_node(Node *head);

void insert_node(Node *head);

void delete_node(Node **head);

void free_list(Node *head);


int main(void){

	size_t size;

	Node *HEAD = NULL;

	printf("WELCOME TO THE LINKED LIST OPS GAME!\n\n");
	printf("Start by initialising a list\n");
	printf("How many Nodes: ");
	scanf("%zu", &size);

	HEAD = create_list(size);

	printf("\nAll %zu", size);
	printf(" Nodes of your linked list have been created\nWhat Next:\n\n");

	int choice;

	while (1)
	{
		printf("\n\n=== _MENU_ ===\n");
		printf("1. Print list (forward)\n");
		printf("2. Print list (backward)\n");
		printf("3. Append a node\n");
		printf("4. Insert a node\n");
		printf("5. Delete node\n");
		printf("0. Exit\n");
		printf("\nChoice: ");

		scanf("%d", &choice);

		if (choice == 0)
		{
			printf("Goodbye!\n");
			break;
		}

		switch (choice)
		{
			case 1:
				print_list_forw(HEAD);
				break;
			case 2:
				print_list_back(HEAD);
				break;
			case 3:
				append_node(HEAD);
				break;
			case 4:
				insert_node(HEAD);
				break;
			case 5:
				delete_node(&HEAD);
				break;
			case 0:
				free_list(HEAD);
				break;
		}
	}
	return 0;
}


// 00. Create list
Node *create_list(size_t size)
{
	Node *head = NULL;
	Node *tmp = NULL;
	Node *tp = NULL;

	for (size_t i = 0; i < size; i++)
	{
		tmp = malloc(sizeof(Node));
		if (tmp == NULL)
		{	
			printf("Memory allocation failed\n");
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

// 1. Print list (forward)
void print_list_forw(Node *head)
{
	if (head == NULL)
		return;
	Node *tp = head;

	// Print while traversing 
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
			printf("   |\n"); 
			printf("   |\n");
			printf("   V\n");
		}
		tp = tp->next;
	}
}

// 2. Print list (backward)
void print_list_back(Node *head)
{
	if (head == NULL)
		return;
	Node *tp = head;

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

		if (tp->prev != NULL)
		{
			printf("   |\n"); 
			printf("   |\n");
			printf("   V\n");
		}
		tp = tp->prev;
	}
}

// 3. Append Node
void append_node(Node *head)
{
	Node *tmp = malloc(sizeof(Node));
	if (tmp == NULL)
	{
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	Node *tp = head;

	while (tp->next != NULL)
	{
		tp = tp->next;
	}
		printf("New Node value: ");
		scanf("%d", &tmp->num);

		tp->next = tmp;
		tmp->prev = tp;
}

// 4. insert node by value
	// does not check for value (O(n) time)
void insert_node(Node *head)
{
	Node *tmp = NULL;
	Node *tp = head;

	Node *new = NULL;

	new = malloc(sizeof(Node));
	if (new == NULL)
	{
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	
	size_t position;
	printf("Which position must this node be: ");
	scanf("%zu", &position);

	printf("What value: ");
	scanf("%d", &new->num);

	for (size_t i = 0; i < (position - 1); i++)
	{
		tp = tp->next;
		if (tp == NULL)
		{
			printf("Position out of linked list bounds");
			exit(EXIT_FAILURE);
		}
	} 
	// set tmp to tp
	tmp = tp->prev;

	new->prev = tmp;
	new->next = tp;

	tp->prev = new;
	tmp->next = new;
}

// 5. Delete a node by value
void delete_node(Node **head)   // needs to modify caller's head
{
    Node *tp = *head;
    Node *tmp = NULL;
    Node *help = NULL;
    int val;

    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Value of pointer: ");
    scanf("%d", &val);

    while (tp != NULL && tp->num != val)
    {
        tp = tp->next;
    }

    if (tp == NULL) {
        printf("Value not found.\n");
        return;
    }

    tmp = tp->next;
    help = tp->prev;

    if (help != NULL)
        help->next = tmp;
    else
        *head = tmp;   // we're deleting the head node

    if (tmp != NULL)
        tmp->prev = help;

    free(tp);
}


// 0. clear the list
void free_list(Node *head)
{
	Node *current = head;

	while (current != NULL)
	{
		Node *next = current->next;
		free(current);
		current = next;
	}
}
