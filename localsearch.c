#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <math.h>
#include "karp.c"

void newInput(long long* newinput, int size, int* solution, long long* array_A) {
  int j; 

  // clear new input
  for (j = 0; j<size; j++){
      newinput[j] = 0; 
  }
  for (j = 0; j<size; j++)
    newinput[solution[j]] += array_A[j]; 
}

float t_iteration(int i) {
  return pow(10, 10) * pow(.8, float(i/300))
}

int* copyRandomSolution(int* original_random_solution, int size) {
  int* copied_random_solution = malloc(sizeof(int) * size);

  int i;
  for (i = 0; i < size; i++) {
    copied_random_solution[i] = original_random_solution[i];
  }
  return copied_random_solution;
}

int* hillClimbingLocalSearch(long long* array_A, int* random_solution, int size, int max_iteration) {

	// logic to create A' list
	long long* newinput = calloc(1, sizeof(long long) * size); 
	struct minHeap* heap = createMinHeap(size);
  // get prior residue
  newInput(newinput, size, random_solution, array_A); 
  initializeMinHeap(heap, newinput, size); 
  long long prior_residue = karp(heap, size);
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
	}

	freeHeap(heap);
	free(newinput);

	return random_solution;
}

int* repeatedRandomLocalSearch(long long* array_A, int* random_solution, int size, int max_iteration) {

  // logic to create A' list
  long long* newinput = calloc(1, sizeof(long long) * size); 
  struct minHeap* heap = createMinHeap(size);
  // get prior residue
  newInput(newinput, size, random_solution, array_A); 
  initializeMinHeap(heap, newinput, size); 
  long long prior_residue = karp(heap, size);
  int j;
  

  int i;
  for (i = 0; i < max_iteration; i++) {
    int* new_random_solution = randomSol(size);

    newInput(newinput, size, new_random_solution, array_A); 
    
    initializeMinHeap(heap, newinput, size); 
    long long new_residue = karp(heap, size);
    if (new_residue < prior_residue) {
      int* temp = random_solution;
      random_solution = new_random_solution;
      free(temp);
    }
      
  }

  freeHeap(heap);
  free(newinput);

  return random_solution;
}

int* simulatedAnnealingLocalSearch(long long* array_A, int* random_solution, int size, int max_iteration) {

  // logic to create A' list
  long long* newinput = calloc(1, sizeof(long long) * size); 
  struct minHeap* heap = createMinHeap(size);
  // get prior residue
  newInput(newinput, size, random_solution, array_A); 
  initializeMinHeap(heap, newinput, size); 

  long long prior_residue = karp(heap, size);

  // S'' residue
  long long original_residue = prior_residue;
  // random_solution2 = S''
  int* random_solution2 = copyRandomSolution(random_solution, size);

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
    else if ((rand() / (double)RAND_MAX) < exp(-(new_residue - prior_residue)/t_iteration(i))) {
      swapArray(random_solution, swapped_elements[0], swapped_elements[1]);
    }

    if (prior_residue < original_residue) {
      original_residue = prior_residue;
      
    }
    
  }

  freeHeap(heap);
  free(newinput);
  return random_solution;
}


int main() {
	srand(time(NULL));
  int size = 10;
  writeFile(size, "input2.txt");
  long long* input = readFile("input2.txt", size); 
  struct minHeap* heap = createMinHeap(size);
  long long* newinput = calloc(1, sizeof(long long) * size); 
  int* random_solution = randomSol(size);

  
  // repeated random test 1
  int* solution1 = repeatedRandomLocalSearch(input, copyRandomSolution(random_solution, size), size, 25000);
  newInput(newinput, size, solution1, input);
  initializeMinHeap(heap, newinput, size); 

  long long final_residue = karp(heap, size);
  printf("Repeated Random Search: \n");
  printf("Solution1: \n"); 
  int j;
  for (j = 0; j<size; j++) {
    printf("%d, ", solution1[j]);
  }
  printf("\n");
  
  printf("The final residue from repeated random sampling was %lli\n", final_residue);
  printf("******************************************************************\n");

  // hill climbing test 2
  int* solution2 = hillClimbingLocalSearch(input, copyRandomSolution(random_solution, size), size, 25000);

  newInput(newinput, size, solution2, input);
  initializeMinHeap(heap, newinput, size); 

  final_residue = karp(heap, size);
  printf("Hill Climbing Search: \n");
  printf("Solution2: \n"); 
  for (j = 0; j<size; j++) {
    printf("%d, ", solution2[j]);
  }
  printf("\n");
  
  printf("The final residue from hill climbing was %lli\n", final_residue);
  printf("******************************************************************\n");


  initializeMinHeap(heap, input, size); 
  printf("Normal karp: \n"); 
  printf("The original normal residue was %lli\n", karp(heap, size));

  free(input);
  free(newinput);
  free(solution1);
  free(solution2);
  freeHeap(heap);
}
