#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "argparse.h"
#include "imclient.h"


static const char *const usage[] = {
    "run in client mode [options] [[--] args]",
    "run in server mode [options] [[--] args]",
    NULL,
};

static struct tinycim_options {
    enum { SERVER_MODE, CLIENT_MODE } mode;
    char *server_address;
    bool is_verbose;
} cli_options;

static const char* translateModeToString(int mode) {
    return mode == CLIENT_MODE ? "client mode" : "server mode";
}

void
printOptions(struct tinycim_options *options);

int main(int argc, char *argv[]) {
    int isClientMode = 0;
    int isServerMode = 0;
    struct argparse_option options[] = {
            OPT_GROUP("Basic options"),
            OPT_BOOLEAN('c', "client", &isClientMode, "use in client mode"),
            OPT_STRING('r', "remote", &cli_options.server_address, "remove server address"),
            OPT_BOOLEAN('s', "server", &isServerMode, "use in server mode"),
            OPT_GROUP("Other options"),
            OPT_BOOLEAN('v', "verbose", &cli_options.is_verbose, "show verbose logs"),
            OPT_HELP(),
            OPT_END(),
    };
    struct argparse argparser;
    argparse_init(&argparser, options, usage, 0);
    argparse_describe(&argparser,
                      "Coconutmilk's Tiny IM",
                      "Writen in CLang with Love.");
    argc = argparse_parse(&argparser, argc, argv);

    if (isClientMode != 0) {
        cli_options.mode = CLIENT_MODE;
    } else {
        cli_options.mode = SERVER_MODE;
    }

    printOptions(&cli_options);
    sayHello();
    exit(EXIT_SUCCESS);
}

void printOptions(struct tinycim_options *options) {
    if (options != NULL) {
        printf("options: mode: %s, addr: %s, verbose: %d\n",
               translateModeToString(options->mode),
               options->server_address,
               options->is_verbose);
    }
}
