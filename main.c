#include <stdio.h>
#include "dynarray.h"

int main() {

    struct dynamic_array *array = array_create(sizeof(int));

    int nums[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        array_push(array, &nums[i]);
    }

    for (int i = 0; i < 5; i++) {
        int val = ((int *)array->data_pointer)[i];
        printf("value at index %d is %d\n", i, val);
    }

    array_free(array);
    return 0;
}