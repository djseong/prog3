#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include "heap.c" 

// read input file and store numbers into nums
int* readFile(char* filename, int d) {
  FILE* f; 
  f = fopen(filename, "r"); 
  if (f == NULL) {
    printf("error opening file\n"); 
    exit(-1); 
  }
  int* nums = malloc(sizeof(int) * d); 
  int i;
  for (i = 0; i < d; i++) {
    fscanf(f, "%d\n", &nums[i]); 
  }
  fclose(f); 
  return nums; 
}

// generate random integers and write to file
void writeFile(int d, char* filename) {
  FILE* f; 
  f = fopen(filename, "w"); 
  if (f == NULL) {
    printf("error writing to file\n"); 
    exit(-1); 
  }
  long long num; 
  int i; 
  for (i = 0; i<d; i++) {
    num = rand() % 1000000000000; 
    fprintf(f, "%lli\n", num); 
  }
  fclose(f); 
}

int karp(struct minHeap* heap, int size) {
  while (heap->size > 1) {
    struct heapNode* firstMax = heapDeleteMin(heap); 
    int newMax = firstMax->value - heap->array[0]->value; 
    heapUpdate(heap, newMax); 
    printHeap(heap);
  }
  return heap->array[0]->value; 
}

int main() {
  srand(time(NULL));
  int size = 100;
  writeFile(size, "input2.txt");
  int* input = readFile("input2.txt", size); 
  int i; 
  for (i = 0; i<size; i++){
    printf("%d\n", input[i]); 
  }
  struct minHeap* heap = createMinHeap(size);
  initializeMinHeap(heap, input, size); 
  buildHeap(heap, size);
  printf("built:\n"); 
  printHeap(heap); 
  printf("running karp:\n"); 
  printf("result: %d\n", karp(heap, size)); 
}
