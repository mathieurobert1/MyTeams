/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** read_flow
*/
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "client.h"
#include <string.h>
#include "shared.h"

static void update_endline_bool(bool *b_r, char *chunk)
{
    if (chunk[0] == '\r')
        (*b_r) = true;
    if (chunk[0] != '\r' && chunk[0] != '\n')
        (*b_r) = false;
}

static char *realloc_if_needed(int csize, int *msize, char **whole_buff)
{
    if (csize >= (*msize)) {
        (*msize) += 200;
        (*whole_buff) = realloc((*whole_buff), sizeof(char) * (*msize));
    }
    return (*whole_buff);
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
        if (!realloc_if_needed(csize, &msize, &whole_buff))
            return NULL;
        strcat(whole_buff, chunk);
        csize++;
        update_endline_bool(&b_r, chunk);
        if ((rn == false && chunk[0] == '\n') || (b_r && chunk[0] == '\n'))
            return whole_buff;
    }
    return NULL;
}

void uinput(client_t *client, fd_set *rdfds, bool *issue)
{
    char *tmp;

    if (FD_ISSET(STDIN_FILENO, rdfds)) {
        tmp = read_flow(STDIN_FILENO, false);
        if (!tmp && !(*issue)) {
            (*issue) = true;
            return;
        }
        write(client->serv_fd, tmp, (strlen(tmp) - 1));
        write(client->serv_fd, "\r\n", 2);
        if (client->last_command_parsed)
            delete_list_arg(client->last_command_parsed);
        client->last_command_parsed = get_list_arg(tmp);
        free(tmp);
    }
}

void read_server(client_t *client, bool *issue)
{
    char *tmp;

    tmp = read_flow(client->serv_fd, true);
    if (!tmp && !(*issue)) {
        (*issue) = true;
        return;
    }
    handle_response(client, tmp);
    free(tmp);
}
