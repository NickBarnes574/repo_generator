#include "dest_paths.h"

void free_dest_paths(char **dest_paths)
{
    for (size_t idx = 0; idx < DEST_NUMBER_OF_CODES; idx++)
    {
        free(dest_paths[idx]);
        dest_paths[idx] = NULL;
    }
}

void destroy_dest_paths(char **dest_paths)
{
    // Destroy each path individually
    free_dest_paths(dest_paths);

    // Destroy the array itself
    free(dest_paths);
    dest_paths = NULL;
}

char **generate_dest_paths(const char *path)
{    
    // Get the project path from the user
    char project_path[512] = "";
    strcpy(project_path, path);

    // Allocate space for the path array
    char **dest_paths = calloc(1, sizeof(char**));
    if (NULL == dest_paths)
    {
        free (dest_paths);
        dest_paths = NULL;
        goto END;
    }

    // Allocate space for each path
    for (size_t idx = 0; idx < DEST_NUMBER_OF_CODES; idx++)
    {
        dest_paths[idx] = calloc(1, sizeof(char*));
        if (NULL == dest_paths[idx])
        {
            destroy_dest_paths(dest_paths);
            goto END;
        }
    }

    /********************************************************
     * NAME: REPO_GENERATOR
     * PATH: user/home/repo_generator
    *********************************************************/
    dest_paths[DEST_DIR_REPO] = project_path;
    const char *repo = dest_paths[DEST_DIR_REPO];

        // default Makefile
        dest_paths[DEST_FILE_DEF_MAKEFILE] = append_path(repo, "Makefile");

        // .gitignore
        dest_paths[DEST_FILE_GITIGNORE] = append_path(repo, ".gitignore");

    /********************************************************
     * NAME: SRC
     * PATH: user/home/repo_generator/save_data/C/src
    *********************************************************/
    dest_paths[DEST_DIR_SRC] = append_path(repo, "src");
    const char *src = dest_paths[DEST_DIR_SRC];

        // main.c
        dest_paths[DEST_FILE_MAIN_C] = append_path(src, "main.c");

        // exit_codes.c
        dest_paths[DEST_FILE_EXIT_CODES_C] = append_path(src, "exit_codes.c");

    /********************************************************
     * NAME: INCLUDE
     * PATH: user/home/repo_generator/save_data/C/include
    *********************************************************/
    dest_paths[DEST_DIR_INCLUDE] = append_path(repo, "include");
    const char *include = dest_paths[DEST_DIR_INCLUDE];

        // main.h
        dest_paths[DEST_FILE_MAIN_H] = append_path(include, "main.h");

        // exit_codes.h
        dest_paths[DEST_FILE_EXIT_CODES_H] = append_path(include, "exit_codes.h");

    /********************************************************
     * NAME: DOCS
     * PATH: user/home/repo_generator/save_data/C/docs
    *********************************************************/
    dest_paths[DEST_DIR_DOCS] = append_path(repo, "docs");

    /********************************************************
     * NAME: TESTS
     * PATH: user/home/repo_generator/save_data/C/test
    *********************************************************/
    dest_paths[DEST_DIR_TEST] = append_path(repo, "test");
    const char *test = dest_paths[DEST_DIR_TEST];

        // tests.c
        dest_paths[DEST_FILE_TESTS] = append_path(test, "tests.c");

        // test_all.c
        dest_paths[DEST_FILE_TEST_ALL] = append_path(test, "test_all.c");

    /********************************************************
     * NAME: TEMPLATES
     * NAME: user/home/repo_generator/save_data/C/templates
    *********************************************************/
    dest_paths[DEST_DIR_TEMPLATES] = append_path(repo, "templates");

END:
    return dest_paths;
}