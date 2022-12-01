#include "main.h"

int main(int argc, char **argv)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    options_t *options = NULL;

    // Initialize signal handler
    signal_setup();

    // Initialize option handler
    options = calloc(1, sizeof(options_t));
    if (NULL == options)
    {
        exit_code = E_CMR_FAILURE;
        goto END;
    }

    // Process and parse command line arguments
    exit_code = process_options(argc, argv, options);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    char **src_paths = generate_src_paths();
    char **dest_paths = generate_dest_paths(options->repo_path);

    // Initialize the repo
    exit_code = initialize_repo(options, src_paths, dest_paths);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;

END:
    free_options(options);
    destroy_src_paths(src_paths);
    destroy_dest_paths(dest_paths);
    return exit_code;
}