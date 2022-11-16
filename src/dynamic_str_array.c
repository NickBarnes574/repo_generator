#include "dynamic_str_array.h"

struct str_arr_
{
    char **str_elements; // Pointer to a dynamic array that will hold [n] number of char* elements
    size_t current_size; // How many elements are currently in the dynamic array
    size_t total_capacity; // How many elements the dynamic array can hold
};

str_arr_t *dystr_create(size_t initial_size)
{
    // 1. Create space on the heap for the struct
    str_arr_t *dyn_str_arr = calloc(1, sizeof(str_arr_t));
    if (NULL == dyn_str_arr)
    {
        return NULL;
    }

    // 2. Create space on the heap for the array
    dyn_str_arr->str_elements = calloc(initial_size, sizeof(char**));
    if (NULL == dyn_str_arr->str_elements)
    {
        free(dyn_str_arr);
        return NULL;
    }
    
    // 3. Initialize dynamic array
    dyn_str_arr->current_size = 0;
    dyn_str_arr->total_capacity = initial_size;

    return dyn_str_arr;
}

void dystr_destroy(str_arr_t *dyn_str_arr)
{
    // 1. Check if a NULL struct pointer was passed
    if (dyn_str_arr == NULL)
    {
        return;
    }

    // 2. Free each element of the dynamic array
    for (size_t idx = 0; idx < dyn_str_arr->current_size; idx++)
    {
        free(dyn_str_arr->str_elements[idx]);
        dyn_str_arr->str_elements[idx] = NULL;
    }
    
    // 3. Free the dynamic array
    free(dyn_str_arr->str_elements);
    dyn_str_arr->str_elements = NULL;

    // 4. Free the struct
    free(dyn_str_arr);
    dyn_str_arr = NULL;
}

exit_code_t dystr_insert_element(str_arr_t *const dyn_str_arr, const char *str)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    // 1. Check if a NULL struct pointer was passed
    if ((NULL == dyn_str_arr) || (NULL == str))
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    // 2. Copy the incoming string and insert it into the dynamic string array
    dyn_str_arr->str_elements[dyn_str_arr->current_size++] = strdup(str);

    // 3. Check if the size of dynamic string array is at the total capacity
    if (dyn_str_arr->current_size == dyn_str_arr->total_capacity)
    {
        dystr_realloc(dyn_str_arr);
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t dystr_realloc(str_arr_t *const dyn_str_arr)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    // 1. Check if dyn_str_arr is NULL
    if (NULL == dyn_str_arr)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    // 1. Reallocate space by doubling the total capacity
    char **temp = realloc(dyn_str_arr->str_elements, (dyn_str_arr->total_capacity * 2) * sizeof(char **));
    if (NULL == temp)
    {
        dyn_str_arr->current_size--; // Decrement the current size
        exit_code = E_NULL_POINTER;
        goto END;
    }

    // 2. Increase the size of the dynamic array
    dyn_str_arr->total_capacity *= 2; // Double the total capacity
    dyn_str_arr->str_elements = temp; // Modify the size of the array

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

char *dystr_get_element(str_arr_t *const dyn_str_arr, size_t index)
{
    char *current_element = NULL;

    // 1. Check if a NULL struct pointer was passed
    if (NULL == dyn_str_arr)
    {
        goto END;
    }

    // 2. Check if the index is within the bounds of the dynamic array
    if (index >= dyn_str_arr->current_size)
    {
        goto END;
    }

    current_element = dyn_str_arr->str_elements[index];
END:
    return current_element;
}

char **dystr_get_list(str_arr_t *const dyn_str_arr)
{
    // 1. Check if a NULL struct pointer was passed
    if (NULL == dyn_str_arr)
    {
        return NULL;
    }

    return dyn_str_arr->str_elements;
}

exit_code_t dystr_set_element(str_arr_t *const dyn_str_arr, size_t index, const char *str)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    // 1. Check if a NULL struct pointer was passed
    if ((NULL == dyn_str_arr) || (NULL == str))
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    // 2. Check if the index is within the bounds of the dynamic array
    if (index >= dyn_str_arr->current_size)
    {
        exit_code = E_OUT_OF_BOUNDS;
        goto END;
    }

    // 3. Delete the old string and replace it with the new string
    free(dyn_str_arr->str_elements[index]);
    dyn_str_arr->str_elements[index] = strdup(str);
    
    exit_code = E_SUCCESS;
END:
    return exit_code;
}

int dystr_get_size(str_arr_t *const dyn_str_arr)
{
    int current_size = 0;

    // 1. Check if a NULL struct pointer was passed
    if (NULL == dyn_str_arr)
    {
        goto END;
    }

    // 2. Get the size of the array
    current_size = (int) dyn_str_arr->current_size;
END:
    return current_size;
}

int dystr_get_total_capacity(str_arr_t *const dyn_str_arr)
{    
    int total_capacity = 0;

    // 1. Check if a NULL struct pointer was passed
    if (NULL == dyn_str_arr)
    {
        goto END;
    }

    // 2. Get the total capacity
    total_capacity = (int) dyn_str_arr->total_capacity;
END:
    return total_capacity;
}
