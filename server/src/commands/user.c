/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** user
*/

#include "types.h"
#include "commands.h"
#include "protocol.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>

static size_t get_size_details(user_t *user)
{
    size_t size = 0;

    size += strlen(user->uuid);
    size += strlen(user->username);
    return size;
}

static char *get_details(user_t *user)
{
    size_t size = get_size_details(user);
    char *details = malloc(size + 2 + 7 + 14);

    if (!details)
        return NULL;
    strcpy(details, "UUID: ");
    strcat(details, user->uuid);
    strcat(details, " , Username: ");
    strcat(details, user->username);
    return details;
}

void user_command(char **command, server_t *myServ, client_t *client)
{
    user_t *user = NULL;

    if (!is_correct_command(&myServ->writefds, command, 1, client->_fd))
        return;
    user = user_get_by_uuid(command[1], myServ->_list_users);
    if (!user) {
        ptc_send(CLIENT_ERROR_UNKNOWN_USER, command[1],
        client->_fd, &myServ->writefds);
        return;
    } else {
        ptc_send(COMMAND_SUCCESS, get_details(user),
        client->_fd, &myServ->writefds);
    }
}
