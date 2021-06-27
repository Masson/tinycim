// Copyright (c) 2021. coconutmilk.io
// Create by Ethan Ma <masson.teng@gmail.com>

#include <stdio.h>
#include <stdlib.h>

#include "imclient.h"
#include "uv.h"

void
say_hello() {
    printf("Hello, World!\n");

    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    printf("Now quitting.\n");
    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);
}