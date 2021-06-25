//
// Created by Ethan Mark on 2021/6/22.
//
#include <stdio.h>
#include <stdlib.h>

#include "imclient.h"
#include "uv.h"

void
sayHello() {
    printf("Hello, World!\n");

    uv_loop_t *loop = malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    printf("Now quitting.\n");
    uv_run(loop, UV_RUN_DEFAULT);

    uv_loop_close(loop);
    free(loop);
}