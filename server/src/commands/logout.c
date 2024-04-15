/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** logout
*/

#include "types.h"
#include "commands.h"
#include "logging_server.h"
#include "protocol.h"
#include "lists.h"
#include "utils.h"

#include <stdio.h>

void logout_command(char **command, server_t *myServ, client_t *client)
{
    client_t *tmp = myServ->_list_client->first;

    if (is_too_more_args(command, 0, client->_fd, &myServ->writefds))
        return;
    server_event_user_logged_out(client->_user_data->uuid);
    while (tmp) {
        if (tmp->_user_data)
            dprintf(tmp->_fd, "%i \"%s\" \"%s\"\r\n", CLIENT_EVENT_LOGGED_OUT,
            client->_user_data->uuid, client->_user_data->username);
        tmp = tmp->_next;
    }
    delete_a_client(client, myServ);
}
