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
  int array[3] = {0,1,2}; 
  FILE* f; 
  f = fopen(filename, "w"); 
  if (f == NULL) {
    printf("error writing to file\n"); 
    exit(-1); 
  }
  int num; 
  int i; 
  int c = d*d*2; 
  for (i = 0; i<c; i++) {
    num = rand() % 3; 
    fprintf(f, "%d\n", array[num]); 
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
  int size = 5; 
  int* input = readFile("input.txt", size); 
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
