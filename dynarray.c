#include <stddef.h>
#include "dynarray.h"
#include <stdlib.h>
#include <string.h>


// HEAP
// ┌─────────────────────────────────────┐
// │         struct dynamic_array        │
// │  data_pointer  │ size │ cap │ esize │
// │      NULL      │  0   │  0  │  0   │
// └─────────────────────────────────────┘



// HEAP
// ┌─────────────────────────────────────┐
// │         struct dynamic_array        │
// │  data_pointer  │ size │ cap │ esize │ 
// │      0x5f3a    │  0   │  4  │  4   │
// └────────┬────────────────────────────┘
//          │
//          ▼
// ┌────────────────────────────────────┐
// │  [ ? ]  [ ? ]  [ ? ]  [ ? ]       │  ← 4 slots for actual data
// └────────────────────────────────────┘
//          0x5f3a


//create and return a new dynamic array struct, pass in the element_size in the parameters
struct dynamic_array * array_create(int element_size) {
    //first create a pointer to the struct itself and allocate it's memory
    struct dynamic_array *array = calloc(1, sizeof(struct dynamic_array));

    //set element size of each element in the array
    array->element_size = element_size;

    //max of 4 items in the array
    array->capacity = 4;
    
    //allocate memory for the data inside of that struct
    array->data_pointer = calloc(array->capacity, element_size);
    return array;
}

//push an item onto the array. requires a pointer to the array struct, and a void* pointer of 
// what you want to add , because if you hardcoded the paramter to a certain type like "int", you would 
//only be able to add integers.
//also double capacity if needed, and increase size after push
void array_push(struct dynamic_array *array, void *item) {

    //check if array is full. if it is, double the capacity
    if (array->size == array->capacity) {
        //double capacity
        array->capacity = array->capacity * 2;
        //copy all data to a new location
        void *temp_pointer = calloc(array->capacity, array->element_size);
        memcpy(temp_pointer, array->data_pointer, array->element_size * array->size);
        //free what the data_pointer was pointing to , then make it point to the new data location
        free(array->data_pointer);
        array->data_pointer = temp_pointer;
    }
    

        
    // NOTE: i thought you could do *((char *)array->data_pointer + array->size * array->element_size) = *item
    // but this is wrong for 2 reasons:
    // 1. dereferencing a char* only gives you 1 byte — so assigning *item to it only copies 1 byte
    // 2. your element might be 4 bytes (int) or more, so you'd corrupt the data
    // that's why you need memcpy — it copies exactly element_size bytes from item into the right slot

    //memcpy(destination, source, num_bytes);
    //(char *)array->data_pointer basically means "treat this pointer like it points to a char" 
    //so that you can do pointer arithmetic on it one byte at a time
    memcpy((char *)array->data_pointer + array->size * array->element_size, item, array->element_size);

    
    array->size++;

}

//requires a pointer to the array struct , and the index of the item you want
void * array_get(struct dynamic_array *array, int index) {
    return (char *)array->data_pointer + (index * array->element_size);
    
}

//requires pointer to array struct. free 2 things: the struct itself, and the pointer field in the 
//struct that is pointing to the data 
void array_free(struct dynamic_array *array) {
    free(array->data_pointer);
    free(array);
}