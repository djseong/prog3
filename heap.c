#include <stdio.h> 
#include <stdlib.h>
#include <limits.h>
#include <math.h> 

// Data structure for a node in heap
struct heapNode {
  int vertex; 
  long long value; 
};

// Data structure for min heap
// Note first element in heap index 0
struct minHeap {
  int size; 
  int capacity;
  struct heapNode **array; 
};

// Debugging function to print heap
void printHeap(struct minHeap* h) {
  int i; 
  int s = h->size; 
  int p; 
  for (i = 0; i < s; i++) {
    p = h->array[i]->value; 
    printf("vertex %d value %d\n", h->array[i]->vertex, p); 
  }
  printf("size: %d\n", h->size); 
}

// Create min heap node
struct heapNode* createMinNode (int v, long long val) {
  struct heapNode* node = malloc(sizeof(struct heapNode)); 
  node->vertex = v; 
  node->value = val; 
  return node; 
}

// Create min heap
struct minHeap* createMinHeap(int capacity) {
  struct minHeap* heap = malloc(sizeof(struct minHeap)); 
  heap->size = 0;
  heap->capacity = capacity; 
  heap->array = (struct heapNode**) malloc(sizeof(struct heapNode*) * capacity); 
  return heap; 
}

// Put first vertex into heap
void initializeMinHeap(struct minHeap* h, long long* input, int size) {
  int i; 
  for (i = 0; i < size; i++) {
    h->array[i] = createMinNode(i, input[i]); 
    h->size++; 
  }
}
  
// Swap two nodes in heap
void swap(int a, int b, struct minHeap* h) {
  struct heapNode* temp = h->array[a]; 
  h->array[a] = h->array[b]; 
  h->array[b] = temp;
}

void minHeapify(struct minHeap* minHeap, int root) {
  int left = root * 2 + 1; 
  int right = root * 2 + 2; 
  int smallest = root; 
  if (minHeap->size > left && 
    minHeap->array[left]->value > minHeap->array[root]->value) {
    smallest = left;  
  }
  if (minHeap->size > right && 
    minHeap->array[right]->value > minHeap->array[smallest]->value) {
    smallest = right; 
  }
  if (smallest != root) {
     swap(root, smallest, minHeap); 
     minHeapify(minHeap, smallest); 
  }
}

// Build heap from array 
void buildHeap(struct minHeap* h, int size) {
  int c = size/2 - 1; 
  int i; 
  for (i = c; i >= 0; i--) {
    minHeapify(h, i);
  }
}

struct heapNode* heapDeleteMin(struct minHeap* h) {
  if (isHeapEmpty(h)) {
    return NULL; 
  }
  struct heapNode* min = h->array[0]; 
  struct heapNode* last = h->array[h->size - 1]; 
  h->array[0] = last;
  h->size--; 
  minHeapify(h, 0); 
  return min; 
}

void heapUpdate(struct minHeap* h, long long val) {
  h->array[0]->value = val; 
  minHeapify(h, 0); 
} 

int isHeapEmpty(struct minHeap* h) {
  return (h->size == 0); 
}

