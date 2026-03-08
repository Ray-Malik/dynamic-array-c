#include <stddef.h>


struct dynamic_array {
    void *data_pointer;
    //current size
    size_t size;
    //max size
    size_t capacity;
    //element size in bytes 
    size_t element_size;
};


struct dynamic_array * array_create(int element_size);
void array_push(struct dynamic_array *array, void *item);
void * array_get(struct dynamic_array *array, int index);
void array_free(struct dynamic_array *array);
