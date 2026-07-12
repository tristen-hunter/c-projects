// Dynamic array implementation in C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int *data;
	size_t length; // elements in use
	size_t capacity; // size of data array (bytes / sizeof(int))
} DynamicArray;



// Responsible for creating the initial array
DynamicArray init_array() {
	DynamicArray da;

	da.data = malloc(256);
	if (da.data == NULL) {
		printf("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	da.length = 0;
	da.capacity = 256 / sizeof(int);

	return da;
}


// Responsible for reallocating the correct amount of memory
void resize_array(DynamicArray *da) {

	printf("Before realloc: %p\n", (void *)da->data);

	// 1. get the current array capacity and reallocate it to double the size
	int *tmp = realloc(da->data, ((da->capacity) * sizeof(int)) * 2);

	printf("After realloc : %p\n", (void *)tmp);

	da->data = tmp;

	// 2. the new capacity is 2x
	da->capacity = (da->capacity) * 2;

	printf(
    	"Resizing: length=%zu capacity=%zu -> %zu\n",
    	da->length,
    	da->capacity,
    	da->capacity * 2
	);
}


// Random number capacity
size_t gen_arr_size(size_t min, size_t max) {
	size_t rand_arr_cap = (rand() % (max - min + 1)) + min;

	return rand_arr_cap;
}


// Random percentage generator
int random_number() {
	return rand() % 101;
}


// Print the array without allowing changes
void print_array(const DynamicArray *da, size_t total_capacity) {
	printf("\nDynamic Array = { ");

	for (size_t i = 0; i < da->length; i++) {
		printf("%d",da->data[i]);

		if (i != da->length - 1) {
			printf(", ");
		}
	} 

	printf(" };\n\n");

	printf("Total Capacity: %zu\n", total_capacity);


}


int main(void) {
	
	printf("Welcome to the resizeable array test circuit: \n");
	printf("On this circut we generate a random number between 1,000 and 10,000 for the total capacity and then random values between 1 and 100.\n");
	printf("The final array is printed at the end\n\n");

	DynamicArray da = init_array();

	srand(time(NULL));


	size_t cap = gen_arr_size(1000, 4000);

	// start appending
	for (size_t i = 0; i < cap; i++) {
		if (da.length == da.capacity){
			resize_array(&da);
		}
		// int ran_val = random_number();

		da.data[da.length] = i;
		da.length++;	
	}

	print_array(&da, da.capacity);
	// printf("Total Capacity: %zu\n", da.capacity);
	
	free(da.data);

	return 0;
}
