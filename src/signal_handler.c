#include "signal_handler.h"

volatile sig_atomic_t abort_program = false;

static void signal_handler(int sig);

void signal_setup()
{
    // Initialize sigaction
    struct sigaction action = {0};

    action.sa_handler = signal_handler;

    // Signal handler
    sigaction(SIGINT, &action, NULL);
}

static void signal_handler(int sig)
{
    switch (sig)
    {

    // Ctrl + C
    case SIGINT:
        abort_program = true;
        break;
    
    default:
        break;
    }
}
