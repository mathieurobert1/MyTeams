/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** read_flow
*/
#include "client.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static void update_endline_bool(bool *b_r, char *chunk)
{
    if (chunk[0] == '\r')
        (*b_r) = true;
    if (chunk[0] != '\r' && chunk[0] != '\n')
        (*b_r) = false;
}

char *read_flow(int fd, bool rn)
{
    int csize = 1;
    int msize = 3;
    char *whole_buff = malloc(sizeof(char)*msize);
    char chunk[2];
    bool b_r = false;

    if (!whole_buff)
        return NULL;
    whole_buff[0] = '\0';
    while (read(fd, chunk, 1) > 0) {
        chunk[1] = '\0';
        if (csize >= msize) {
            msize += 200;
            whole_buff = realloc(whole_buff, sizeof(char) * msize);
        }
        strcat(whole_buff, chunk);
        csize++;
        update_endline_bool(&b_r, chunk);
        if ((rn == false && chunk[0] == '\n') || (b_r && chunk[0] == '\n'))
            return whole_buff;
    }
    return NULL;
}
