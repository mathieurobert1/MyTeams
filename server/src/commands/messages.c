/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** messages
*/

#include "types.h"
#include "utils.h"
#include "protocol.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

static int get_size_message(user_t *user, char *uuid_dest)
{
    int size = 0;
    message_t *tmp = user->messages->first;

    while (tmp) {
        if (strcmp(tmp->sender_uuid, uuid_dest) == 0 &&
        strcmp(tmp->receiver_uuid, user->uuid) == 0)
            size += strlen(tmp->message) + 2;
        if (strcmp(tmp->receiver_uuid, uuid_dest) == 0 &&
        strcmp(tmp->sender_uuid, user->uuid) == 0)
            size += strlen(tmp->message) + 2;
        tmp = tmp->next;
    }
    return size;
}

static char *get_messages(user_t *user, char *uuid_dest)
{
    char *messages = malloc(get_size_message(user, uuid_dest) + 1);
    message_t *tmp = user->messages->first;

    if (!messages)
        return NULL;
    memset(messages, 0, get_size_message(user, uuid_dest) + 1);
    while (tmp) {
        if (strcmp(tmp->sender_uuid, uuid_dest) == 0 &&
        strcmp(tmp->receiver_uuid, user->uuid) == 0) {
            strcat(messages, tmp->message);
            strcat(messages, "\n");
        }
        if (strcmp(tmp->receiver_uuid, uuid_dest) == 0 &&
        strcmp(tmp->sender_uuid, user->uuid) == 0) {
            strcat(messages, tmp->message);
            strcat(messages, "\n");
        }
        tmp = tmp->next;
    }
    return messages;
}

void messages_command(char **command, server_t *myServ, client_t *client)
{
    user_t *user = NULL;

    if (!is_correct_command(&myServ->writefds, command, 1, client->_fd))
        return;
    user = get_user_by_uuid(command[1], myServ);
    if (!user) {
        ptc_send(UNKNOWN_USER, "Unknown user", client->_fd, &myServ->writefds);
        return;
    } else {
        ptc_send(COMMAND_SUCCESS, get_messages(user, client->_user_data->uuid),
        client->_fd, &myServ->writefds);
    }
}
