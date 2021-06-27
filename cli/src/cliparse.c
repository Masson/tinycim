// Copyright (c) 2021. coconutmilk.io
// Create by Ethan Ma <masson.teng@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cliparse.h"
#include "common.h"


void cliparse_init(
        struct cliparse *self, struct cliparse_command *commands, int command_count,
        const char *welcome_text, const char *goodbye_text, int flags) {
    self->welcome_text = welcome_text;
    self->goodbye_text = goodbye_text;
    self->commands = commands;
    self->command_count = command_count;
    self->flags = flags;
}

enum cliparse_result parse_line(struct cliparse *self, const char *line);

int cliparse_listen(struct cliparse *self) {
    if (self->commands == NULL || self->command_count <= 0) {
        fprintf(stderr, "no command found on cliparse!");
        return EXIT_FAILURE;
    }

    if (self->welcome_text) {
        fputs(self->welcome_text, stdout);
        fputc('\n', stdout);
    }

    char line[LINE_MAX_LENGTH];
    int i;
    // repeat scan user's input as command
    while (1) {
        fputc('>', stdout);
        if (fgets(line, LINE_MAX_LENGTH, stdin) != NULL && line[0] != '\n') {
            i = 0;
            while (line[i] != '\n' && line[i] != '\0') {
                i++;
            }
            // Make the line's length always < LINE_MAX_LENGTH.
            if (line[i] == '\n') {
                // no return
                line[i] = '\0';
            } else {  // line[i] == '\0'
                while (getchar() != '\n') {
                    // skip the rest char(s).
                }
            }

            // parse and invoke the line as command
            enum cliparse_result result = parse_line(self, line);
            if (result == CLIPARSE_ERROR) {
                fprintf(stderr, "error on parse command line: %s\n", line);
            } else if (result == CLIPARSE_EXIT) {
                break;
            }
        }
    }
    return EXIT_SUCCESS;
}

enum cliparse_result parse_line(struct cliparse *self, const char *line) {
    char line_command[COMMAND_MAX_LENGTH];
    char line_input[INPUT_MAX_LENGTH];

    // parse command name
    int i = 0;
    while (line[i] != '\n' && line[i] != '\0' && line[i] != ' ' && i < COMMAND_MAX_LENGTH) {
        line_command[i] = line[i];
        i++;
    }
    line_command[i] = '\0';

    // parse input argument
    int j = 0;
    if (line[i] != '\n' && line[i] != '\0') {
        i++;
        while (line[i] != '\n' && line[i] != '\0' && i < LINE_MAX_LENGTH) {
            line_input[j] = line[i];
            i++;
            j++;
        }
    }
    line_input[j] = '\0';

    // DEBUG
//    fprintf(stdout, "line: %s, command: %s, input: %s\n", line, line_command, line_input);

    bool matched = false;
    for (int i = 0; i < self->command_count; ++i) {
        const struct cliparse_command command = self->commands[i];
        if (strcmp(command.command, line_command) == 0) {
            // match command
            matched = true;
            // DEBUG
//            fprintf(stdout, "matched command: %s, usage: %s\n", line_command, command.usage);
            if (command.listener != NULL) {
                return command.listener(self, &command, line_input);
            }
        }
    }

    if (!matched) {
        fprintf(stdout, "No command match: %s\n", line);
    }

    return CLIPARSE_CONTINUE;
}

enum cliparse_result cliparse_usage(
        struct cliparse *self,
        const struct cliparse_command *cmd,
        const char *input) {
    fputs("Usage: <command> [arguments...]\n", stdout);

    // figure out best width for command
    size_t max_len = 0;
    size_t len = 0;
    for (int i = 0; i < self->command_count; ++i) {
        const struct cliparse_command command = self->commands[i];
        len = strlen(command.command);
        if (len > max_len) {
            max_len = len;
        }
    }

    // print all usage for each command
    for (int i = 0; i < self->command_count; ++i) {
        const struct cliparse_command command = self->commands[i];
        fprintf(stdout, "   %-*s  %s\n", (int) max_len, command.command, command.usage);
    }
    fputc('\n', stdout);
    return CLIPARSE_CONTINUE;
}

enum cliparse_result cliparse_exit(
        struct cliparse *self,
        const struct cliparse_command *cmd,
        const char *input) {
    if (self->goodbye_text) {
        fputs(self->goodbye_text, stdout);
    }
    return CLIPARSE_EXIT;
}