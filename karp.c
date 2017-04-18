#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include "heap.c" 

// read input file and store numbers into nums
unsigned long long* readFile(char* filename, int d) {
  FILE* f; 
  f = fopen(filename, "r"); 
  if (f == NULL) {
    printf("error opening file\n"); 
    exit(-1); 
  }
  unsigned long long* nums = malloc(sizeof(unsigned long long) * d); 
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
  unsigned long long num; 
  int i; 
  for (i = 0; i<d; i++) {
    num = (float) pow(10, 12) * rand()/RAND_MAX;
    // num = rand() % 10; 
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

// Function to Merge Arrays L and R into A. 
// lefCount = number of elements in L
// rightCount = number of elements in R. 
void Merge(unsigned long long* A,unsigned long long* L,int leftCount,unsigned long long* R, int rightCount) {
  int i,j,k;

  // i - to mark the index of left aubarray (L)
  // j - to mark the index of right sub-raay (R)
  // k - to mark the index of merged subarray (A)
  i = 0; j = 0; k =0;

  while(i<leftCount && j< rightCount) {
    if(L[i] > R[j]) A[k++] = L[i++];
    else A[k++] = R[j++];
  }
  while(i < leftCount) A[k++] = L[i++];
  while(j < rightCount) A[k++] = R[j++];
}

// Recursive function to sort an array of integers. 
void MergeSort(unsigned long long *A,int n) {
  int mid,i;
  unsigned long long *L, *R;
  if(n < 2) return; // base condition. If the array has less than two element, do nothing. 

  mid = n/2;  // find the mid index. 

  // create left and right subarrays
  // mid elements (from index 0 till mid-1) should be part of left sub-array 
  // and (n-mid) elements (from mid to n-1) will be part of right sub-array
  L = (unsigned long long*)malloc(mid*sizeof(unsigned long long)); 
  R = (unsigned long long*)malloc((n- mid)*sizeof(unsigned long long)); 
  
  for(i = 0;i<mid;i++) L[i] = A[i]; // creating left subarray
  for(i = mid;i<n;i++) R[i-mid] = A[i]; // creating right subarray

  MergeSort(L,mid);  // sorting the left subarray
  MergeSort(R,n-mid);  // sorting the right subarray
  Merge(A,L,mid,R,n-mid);  // Merging L and R into A as sorted list.
        free(L);
        free(R);
}

unsigned long long karp2(unsigned long long* num_list, int size) {
  MergeSort(num_list, size);
  int count = size;
  while (count > 1) {
    unsigned long long new_val = num_list[0] - num_list[1];
    num_list[0] = new_val;
    num_list[1] = 0;
    MergeSort(num_list, size);
    count--;
  }
  MergeSort(num_list, size);
  return num_list[0];
}


unsigned long long karp(struct minHeap* heap, int size) {
  buildHeap(heap, size);
  while (heap->size > 1) {
    struct heapNode* firstMax = heapDeleteMin(heap); 
    unsigned long long newMax = firstMax->value - heap->array[0]->value; 
    heapUpdate(heap, newMax); 
    //printHeap(heap);
  }
  return heap->array[0]->value; 
}


