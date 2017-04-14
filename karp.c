#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include "heap.c" 

// read input file and store numbers into nums
long long* readFile(char* filename, int d) {
  FILE* f; 
  f = fopen(filename, "r"); 
  if (f == NULL) {
    printf("error opening file\n"); 
    exit(-1); 
  }
  long long* nums = malloc(sizeof(long long) * d); 
  int i;
  for (i = 0; i < d; i++) {
    fscanf(f, "%lli\n", &nums[i]); 
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
    //num = rand() % 1000000000000; 
    num = rand() % 10; 
    fprintf(f, "%lli\n", num); 
  }
  fclose(f); 
}

int* randomSol(int n) {
  int* num = malloc(sizeof(int) * n); 
  int i; 
  for (i = 0; i < n; i++) {
    num[i] = rand() % n; 
  }
  return num; 
}

long long karp(struct minHeap* heap, int size) {
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
  int size = 5;
  writeFile(size, "input2.txt");
  long long* input = readFile("input2.txt", size); 
  int* partition = randomSol(size); 
  long long* newinput = calloc(1, sizeof(long long) * size); 
  int i; 
  printf("old input:\n"); 
  for (i = 0; i < size; i++)
    printf("%lli\n", input[i]);
  for (i = 0; i<size; i++){
     newinput[partition[i]] += input[i]; 
  }
  printf("partition: \n"); 
  for (i = 0; i < size; i++)
    printf("%d\n", partition[i]); 
  printf("new input:\n"); 
  for (i = 0; i < size; i++)
    printf("%lli\n", newinput[i]);
  struct minHeap* heap = createMinHeap(size);
  initializeMinHeap(heap, newinput, size); 
  buildHeap(heap, size);
  printf("built:\n"); 
  printHeap(heap); 
  printf("running karp:\n"); 
  printf("result: %lli\n", karp(heap, size)); 
}
