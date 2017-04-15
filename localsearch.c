#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include "karp.c"

void newInput(long long* newinput, int size, int* solution, long long* array_A) {
  int j; 
  for (j = 0; j<size; j++)
    newinput[solution[j]] += array_A[j]; 
}


int* repeatedRandomLocalSearch(long long* array_A, int size, int max_iteration) {
	int* random_solution = randomSol(size);

	// logic to create A' list
	long long* newinput = calloc(1, sizeof(long long) * size); 
	struct minHeap* heap = createMinHeap(size);
  // get prior residue
  newInput(newinput, size, random_solution, array_A); 
  initializeMinHeap(heap, newinput, size); 
  long long prior_residue = karp(heap, size);
  int j;
  for (j = 0; j<size; j++){
      newinput[j] = 0; 
  }
	int i;
	for (i = 0; i < max_iteration; i++) {
		int* swapped_elements = randomMove(random_solution, size);
		newInput(newinput, size, random_solution, array_A); 
    // for (j = 0; j<size; j++) {
    // printf("%d\n", random_solution[j]);
    // }
		initializeMinHeap(heap, newinput, size); 
		long long new_residue = karp(heap, size);
		if (new_residue < prior_residue)
			swapArray(random_solution, swapped_elements[0], swapped_elements[1]);
    for (j = 0; j<size; j++){
      newinput[j] = 0; 
    }
	}

	freeHeap(heap);
	// fflush(stdout);
	free(newinput);

	return random_solution;
}

int main() {
	srand(time(NULL));
  int size = 5;
  writeFile(size, "input2.txt");
  long long* input = readFile("input2.txt", size); 
  
  int* solution = repeatedRandomLocalSearch(input, size, 5);


  struct minHeap* heap = createMinHeap(size);
  long long* newinput = calloc(1, sizeof(long long) * size); 
	int j;
	for (j = 0; j<size; j++){
    newinput[solution[j]] += input[j];
  }
  initializeMinHeap(heap, newinput, size); 

  long long final_residue = karp(heap, size);
  printf("Repeated random search: \n");
  printf("Solution: \n"); 
  for (j = 0; j<size; j++) {
    printf("%d\n", solution[j]);
  }
  printf("The final residue was %lli\n", final_residue);
  initializeMinHeap(heap, input, size); 
  printf("Normal karp: \n"); 
  printf("The final residue was %lli\n", karp(heap, size));

  free(input);
  free(newinput);
  free(solution);
  freeHeap(heap);
}
