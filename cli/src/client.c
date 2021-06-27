// Copyright (c) 2021. coconutmilk.io
// Create by Ethan Ma <masson.teng@gmail.com>

#include <stdlib.h>
#include <stdio.h>

#include "client.h"
#include "cliparse.h"
#include "common.h"


enum cliparse_result on_send_command(
        struct cliparse *self,
        const struct cliparse_command *cmd,
        const char *input);

int enter_client_mode() {
    struct cliparse_command commands[] = {
            {"send", "<text> send a message with <text>", on_send_command },
            COMMAND_USAGE(),
            COMMAND_EXIT(),
    };
    struct cliparse cliparse;
    cliparse_init(&cliparse, commands, ARRAY_SIZE(commands),
                  "Tinycim CLI from coconutmilk.io",
                  "Tinycim CLI now exited.",
                  0);
    cliparse_listen(&cliparse);

    return EXIT_SUCCESS;
}

enum cliparse_result on_send_command(
        struct cliparse *self,
        const struct cliparse_command *cmd,
        const char *input) {
    fprintf(stdout, "test send: %s\n", input);
    return CLIPARSE_CONTINUE;
}