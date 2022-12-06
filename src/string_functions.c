#include "string_functions.h"

// exit_code_t str_to_upper(char **str)
// {
//     exit_code_t exit_code = E_DEFAULT_ERROR;

//     if (NULL == str)
//     {
//         exit_code = E_NULL_POINTER;
//         goto END;
//     }

//     for (size_t idx = 0; *str[idx] != '\0'; idx++)
//     {
//         if (*str[idx] >= 'a' && *str[idx] <= 'z')
//         {
//             *str[idx] = *str[idx] - 32;
//         }
//     }

//     exit_code = E_SUCCESS;
// END:
//     return exit_code;
// }

char *str_toupper(char *string)
{
    if (NULL == string)
    {
        return NULL;
    }

    char str[3000];
    strcpy(str, string);

    for (size_t idx = 0; str[idx] != '\0'; idx++)
    {
        if (str[idx] >= 'a' && str[idx] <= 'z')
        {
            str[idx] = str[idx] - 32;
        }
    }

    return strdup(str);
}