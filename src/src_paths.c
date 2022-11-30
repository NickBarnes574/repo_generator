#include "src_paths.h"

void free_paths(src_codes_t src_codes, char **src_paths)
{
    for (size_t idx = 0; idx < src_codes; idx++)
    {
        free(src_paths[idx]);
        src_paths[idx] = NULL;
    }
}

char **generate_src_paths()
{
    // Get the user's home directory
    const char *home = (const char*)getenv("HOME");

    src_codes_t src_codes;

    // Allocate space for the path array
    char **src_paths = calloc(1, sizeof(char**));
    if (NULL == src_paths)
    {
        free (src_paths);
        src_paths = NULL;
        goto END;
    }

    // Allocate space for each path
    for (size_t idx = 0; idx < src_codes; idx++)
    {
        src_paths[idx] = calloc(1, sizeof(char*));
        if (NULL == src_paths[idx])
        {
            free_paths(src_codes, src_paths);
            free(src_paths);
            src_paths = NULL;
            goto END;
        }
    }

    // Create top level directories
    src_paths[DIR_REPO] = append_path(home, "repo_generator");
    const char *repo = src_paths[DIR_REPO];

    src_paths[DIR_SAVE_DATA] = append_path(repo, "save_data");
    const char *save_data = src_paths[DIR_SAVE_DATA];

    src_paths[DIR_C] = append_path(save_data, "C");
    const char *c = src_paths[DIR_C];

    // Create project directories
    src_paths[DIR_SRC] = append_path(c, "src");
    const char *src = src_paths[DIR_SRC];

    src_paths[DIR_INCLUDE] = append_path(c, "include");
    const char *include = src_paths[DIR_INCLUDE];

    src_paths[DIR_DOCS] = append_path(c, "docs");
    const char *docs = src_paths[DIR_DOCS];

    src_paths[DIR_TEST] = append_path(c, "test");
    const char *test = src_paths[DIR_TEST];

    src_paths[DIR_TEMPLATES] = append_path(c, "templates");
    const char *templates = src_paths[DIR_TEMPLATES];

    src_paths[FILE_DEF_MAKEFILE] = append_path(c, "Makefile");


END:
    return src_paths;
}