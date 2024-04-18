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
#include <string.h>

static bool is_user_connected_to_another_client(server_t *myServ,
    char *uuid_user, int fd_current_client)
{
    client_t *tmp = myServ->_list_client->first;

    while (tmp) {
        if (tmp->_fd != fd_current_client && tmp->_user_data &&
            strcmp(tmp->_user_data->uuid, uuid_user) == 0)
                return true;
        tmp = tmp->_next;
    }
    return false;
}

void logout_command(char **command, server_t *myServ, client_t *client)
{
    client_t *tmp = myServ->_list_client->first;

    if (is_too_more_args(command, 0, client->_fd, &myServ->writefds))
        return;
    if (!client->_user_data) {
        delete_a_client(client, myServ);
        return;
    }
    server_event_user_logged_out(client->_user_data->uuid);
    if (!is_user_connected_to_another_client(myServ, client->_user_data->uuid,
        client->_fd))
        client->_user_data->is_logged = false;
    while (tmp) {
        if (tmp->_user_data && FD_ISSET(tmp->_fd, &myServ->writefds))
            dprintf(tmp->_fd, "%i \"%s\" \"%s\"\r\n", CLIENT_EVENT_LOGGED_OUT,
            client->_user_data->uuid, client->_user_data->username);
        tmp = tmp->_next;
    }
    delete_a_client(client, myServ);
}
