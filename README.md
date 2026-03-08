# Dynamic Array Library

A generic dynamic array implemented in C. Stores any data type using `void*` pointers and automatically doubles capacity when full.

## API

```c
struct dynamic_array *array_create(int element_size);
void   array_push(struct dynamic_array *array, void *item);
void  *array_get(struct dynamic_array *array, int index);
void   array_free(struct dynamic_array *array);
```

## Usage

```c
#include "dynarray.h"

int nums[] = {10, 20, 30, 40, 50};
struct dynamic_array *array = array_create(sizeof(int));

for (int i = 0; i < 5; i++) {
    array_push(array, &nums[i]);
}

int val = *(int *)array_get(array, 0);  // 10

array_free(array);
```

## How it works

- Starts with capacity of 4 elements
- When full, allocates a new block double the size, copies all data over, and frees the old block
- Uses `char*` casting for byte-level pointer arithmetic to stay type-agnostic
- Caller is responsible for passing the correct element size at creation

## Build

```
gcc main.c dynarray.c -o main
```