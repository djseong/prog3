#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include "karp.c"




int* repeatedRandomLocalSearch(long long* array_A, int size, int max_iteration) {
	int* random_solution = randomSol(size);

	// logic to create A' list
	long long* newinput = calloc(1, sizeof(long long) * size); 
	
	struct minHeap* heap = createMinHeap(size);



	int i;
	for (i = 0; i < max_iteration; i++) {
		int j;
		for (j = 0; j<size; j++){
	    newinput[random_solution[j]] += array_A[j]; 
	  }

	  initializeMinHeap(heap, newinput, size); 
		long long prior_residue = karp(heap, size);
		int* swapped_elements = randomMove(random_solution, size);
		for (j = 0; j<size; j++){
	    newinput[random_solution[j]] += array_A[j]; 
	  }
		initializeMinHeap(heap, newinput, size); 
		long long new_residue = karp(heap, size);
		if (new_residue < prior_residue) {
			swapArray(random_solution, swapped_elements[0], swapped_elements[1]);
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
  
  int* solution = repeatedRandomLocalSearch(input, size, 10);


  struct minHeap* heap = createMinHeap(size);
  long long* newinput = calloc(1, sizeof(long long) * size); 
	int j;
	for (j = 0; j<size; j++){
    newinput[solution[j]] += input[j];

  }
	initializeMinHeap(heap, newinput, size); 

  long long final_residue = karp(heap, size);

  printf("The final residue was %lli", final_residue);

  free(input);
  free(newinput);
  free(solution);
  freeHeap(heap);
}