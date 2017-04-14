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

void swapArray(int* array, int i, int j) {
  int temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}
// randomly choose two indices i and j and swap those positions in P array
int* randomMove(int* array_P, int size) {
  int random_index1 = rand() % size;

  int random_index2 = rand() % size;
  while (random_index2 == random_index1) {
    random_index2 = rand() % size;
  }

  int* swapped_elements = malloc(sizeof(int) * 2);
  swapped_elements[0] = random_index1;
  swapped_elements[1] = random_index2;
  swapArray(array_P, random_index1, random_index2);
  return swapped_elements;
}

long long karp(struct minHeap* heap, int size) {
  buildHeap(heap, size);
  while (heap->size > 1) {
    struct heapNode* firstMax = heapDeleteMin(heap); 
    int newMax = firstMax->value - heap->array[0]->value; 
    heapUpdate(heap, newMax); 
    printHeap(heap);
  }
  return heap->array[0]->value; 
}

