// Fixed Array Implementation

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

typedef struct {
	int *data;
	size_t length;
} FixedArray;


// For the memory allocation and validation
FixedArray create_array(size_t size){

	if (size == 0) {
		printf("Array size must be greater than 0\n");
		exit(EXIT_FAILURE);
	}

	if (size > SIZE_MAX / sizeof(int)) {
		printf("Requested array is too large\n");
		exit(EXIT_FAILURE);
	}

	FixedArray array;

	array.data = malloc(size * sizeof(int));
	
	if (array.data == NULL) {
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	array.length = size;

	return array;
}

// Fill the arrray, loop size number of times
void fill_array(FixedArray *array){
	for (size_t i = 0; i < array->length; i++){
		printf("Enter number %zu: ", i + 1);

		if (scanf("%d", &array->data[i]) != 1) {
			printf("Error: invalid input, redoing this value.\n\n");
			
			// 1. clear the bad input from the buffer
			int c;
			while ((c = getchar()) != '\n' && c != EOF);

			// 2. decrement the counter so the round repeats
			i--;

			// 3. skip the rest of the code and restart the loop
			continue;
		}
	}
}

// Print the array without allowing changes
void print_array(const FixedArray *array) {
	printf("\narray = { ");

	for (size_t i = 0; i < array->length; i++) {
		printf("%d",array->data[i]);

		if (i != array->length - 1) {
			printf(", ");
		}
	} 

	printf(" };\n");
}	

void destroy_array(FixedArray *array) {
	free(array->data);

	array->data = NULL;
	array->length = 0;
}

int main(void) {
	size_t size;

	printf("Enter array size: ");
	scanf("%zu", &size);

	printf("\n");

	FixedArray array = create_array(size);
	fill_array(&array);
	print_array(&array);

	destroy_array(&array);

	return 0;
}
