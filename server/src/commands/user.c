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

static int get_size_details(user_t *user)
{
    int size = 0;

    size += strlen(user->uuid);
    size += strlen(user->username);
    return size;
}

static char *get_details(user_t *user)
{
    char *details = malloc(get_size_details(user) + 2 + 7 + 14);

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
    user = get_user_by_uuid(command[1], myServ);
    if (!user) {
        ptc_send(UNKNOWN_USER, "Unknown user", client->_fd, &myServ->writefds);
        return;
    } else {
        ptc_send(COMMAND_SUCCESS, get_details(user),
        client->_fd, &myServ->writefds);
    }
}
