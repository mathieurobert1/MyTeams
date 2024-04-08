/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** user
*/

#include "types.h"
#include "commands.h"
#include "protocol.h"

user_t *getUserByUuid(char *uuid, server_t *myServ)
{
    user_list_t *list = myServ->_list_users;
    user_t *user = list->first;

    for (size_t i = 0; user != NULL; i++) {
        if (strcmp(user->uuid, uuid) == 0)
            return user;
        user = user->next;
    }
    return NULL;
}

int getSizeDetails(user_t *user)
{
    int size = 0;

    size += strlen(user->uuid);
    size += strlen(user->username);
    return size;
}

char *getDetails(user_t *user)
{
    char *details = malloc(getSizeDetails(user) + 2);

    if (!details)
        return NULL;
    strcpy(details, user->uuid);
    strcat(details, user->username);
    return details;
}

void user_command(char **command, server_t *myServ, client_t *client)
{
    user_t *user = NULL;

    if (!is_correct_command(&myServ->writefds, command, 1, client->_fd))
        return;
    user = getUserByUuid(client->_user_data->uuid, myServ);
    if (!user) {
        ptc_send(UNKNOWN_USER, "Unknown user", client->_fd, &myServ->writefds);
        return;
    } else {
        ptc_send(COMMAND_SUCCESS, getDetails(user), client->_fd, &myServ->writefds);
    }
}
