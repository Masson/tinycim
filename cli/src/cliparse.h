// Copyright (c) 2021. coconutmilk.io
// Create by Ethan Ma <masson.teng@gmail.com>

#ifndef TINYCIM_CLIPARSE_H
#define TINYCIM_CLIPARSE_H

#define LINE_MAX_LENGTH         80
#define COMMAND_MAX_LENGTH      20
#define INPUT_MAX_LENGTH        (LINE_MAX_LENGTH - COMMAND_MAX_LENGTH)

/* For c++ compatibility */
#ifdef __cplusplus
extern "C" {
#endif

struct cliparse;
struct cliparse_command;

enum cliparse_result {
    CLIPARSE_CONTINUE       = 0,
    CLIPARSE_EXIT           = 1,
    CLIPARSE_ERROR          = 2,
};

/**
 * callback function that trigger by command.
 */
typedef enum cliparse_result cmd_listener (struct cliparse *self,
                                           const struct cliparse_command *cmd,
                                           const char *input);

/**
 * Cliparse is tool to parse user's input repeatedly on each line.
 */
struct cliparse {
    const char *welcome_text;
    const char *goodbye_text;
    const struct cliparse_command *commands;
    int command_count;
    int flags;
};

/**
 * single command for Cliparse.
 *
 * @param command
 *      the command name to match
 * @param usage
 *      the help message display on 'usage' command
 * @param listener
 *      the callback function that trigger by this command
 */
struct cliparse_command {
    const char *command;
    const char *usage;
    cmd_listener *listener;
};

// built-in command listener
enum cliparse_result cliparse_usage(
        struct cliparse *self,
        const struct cliparse_command *cmd,
        const char *input);
enum cliparse_result cliparse_exit(
        struct cliparse *self,
        const struct cliparse_command *cmd,
        const char *input);

// built-in commands
#define COMMAND_USAGE()     { "usage", "show usage of all commands", cliparse_usage }
#define COMMAND_EXIT()      { "exit", "exit the CLI application", cliparse_exit }

/**
 * init cliparse instance
 */
void cliparse_init(
        struct cliparse *self, struct cliparse_command *commands, int command_count,
        const char *welcome_text, const char *goodbye_text, int flags);

/**
 * start listen and handle user's input
 *
 * @param self
 *      the cliparse instance
 * @return
 *      the exit code for the program. see EXIT_SUCCESS or EXIT_FAILURE on 'stdlib.h'
 */
int cliparse_listen(struct cliparse *self);

#ifdef __cplusplus
}
#endif

#endif //TINYCIM_CLIPARSE_H
