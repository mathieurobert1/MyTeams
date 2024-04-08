/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** users
*/

#include "types.h"
#include "commands.h"
#include "protocol.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>

static int getSizeMessage(user_list_t *user_list)
{
    int size = 0;
    user_t *tmp = user_list->first;

    while (tmp != NULL) {
        size += strlen(tmp->username) + 3 + strlen(tmp->uuid) + 2;
        tmp = tmp->next;
    }
    return size;
}

static char *getMessage(user_list_t *user_list)
{
    int size = getSizeMessage(user_list);
    char *msg = malloc(sizeof(char) * (size + 1));
    user_t *tmp = user_list->first;

    if (!msg)
        return NULL;
    memset(msg, 0, size + 1);
    strcat(msg, "[");
    while (tmp->next != NULL) {
        strcat(msg, tmp->username);
        strcat(msg, " : ");
        strcat(msg, tmp->uuid);
        strcat(msg, ", ");
        tmp = tmp->next;
    }
    strcat(msg, tmp->username);
    strcat(msg, " : ");
    strcat(msg, tmp->uuid);
    strcat(msg, "]");
    return msg;
}

void users_command(char **command, server_t *myServ, client_t *client)
{
    user_list_t *user_list = myServ->_list_users;
    char *msg = NULL;

    if (is_correct_command(&myServ->writefds, command, 0, client->_fd) == false)
        return;
    msg = getMessage(user_list);
    ptc_send(COMMAND_SUCCESS, msg, client->_fd, &myServ->writefds);
    if (msg != NULL)
        free(msg);
}
