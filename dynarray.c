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