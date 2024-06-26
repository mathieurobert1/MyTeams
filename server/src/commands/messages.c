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
#include <stdio.h>

static void print_messages(user_t *user, client_t *client, server_t *server)
{
    message_t *tmp = user->messages->first;
    char *uuid_dest = client->_user_data->uuid;

    while (tmp) {
        if (strcmp(tmp->sender_uuid, uuid_dest) == 0 &&
            strcmp(tmp->receiver_uuid, user->uuid) == 0 &&
            FD_ISSET(client->_fd, &server->writefds)) {
                dprintf(client->_fd, "%d \"%s\" \"%ld\" \"%s\"\r\n",
                    CLIENT_PRIVATE_MESSAGE_PRINT_MESSAGES, tmp->sender_uuid,
                    tmp->timestamp, tmp->message);
        }
        if (strcmp(tmp->receiver_uuid, uuid_dest) == 0 &&
            strcmp(tmp->sender_uuid, user->uuid) == 0 &&
            FD_ISSET(client->_fd, &server->writefds)) {
                dprintf(client->_fd, "%d \"%s\" \"%ld\" \"%s\"\r\n",
                    CLIENT_PRIVATE_MESSAGE_PRINT_MESSAGES, tmp->sender_uuid,
                    tmp->timestamp, tmp->message);
        }
        tmp = tmp->next;
    }
}

void messages_command(char **command, server_t *myServ, client_t *client)
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
        print_messages(user, client, myServ);
    }
}
