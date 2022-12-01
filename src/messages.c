#include "messages.h"

const char *msg_notice()
{
    return "\n----------------NOTICE----------------\n";
}

const char *msg_check_save_dir()
{
    return "\n--------CHECKING SAVE DIRECTORY--------\n";
}

const char *msg_init_save_dir()
{
    return "\n------INITIALIZING SAVE DIRECTORY------\n";
}

const char *msg_init_repo(char **src_paths)
{
    char message[512] = "";
    strcpy(message, msg_notice());
    strcat(message, "This will initialize the following path as a C repository:\n\nREPOSITORY: [");
    strcat(message, src_paths[SRC_DIR_REPO]);
    strcat(message, "]\n\nDo you wish to continue? [Y]/[N] ");

    return message;
}

const char *msg_init_save_data(char **src_paths)
{
    char message[512] = "";
    strcpy(message, "\nNOTICE: [NO SAVE DATA FOUND]\n\n");
    strcpy(message, "To continue, a new save directory must be initialized.\n");
    strcat(message, "A new save directory will be created at the following location:\n\nSAVE DIRECTORY: [");
    strcat(message, src_paths[SRC_DIR_SAVE_DATA]);
    strcat(message, "]\n\nDo you wish to continue? [Y]/[N] ");
}