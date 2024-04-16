/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** login
*/

#include "types.h"
#include "protocol.h"
#include "commands.h"
#include "lists.h"
#include "logging_server.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static bool is_user_name_too_long(char **command, client_t *client,
    server_t *myServ)
{
    if (strlen(command[1]) > MAX_NAME_LENGTH) {
        ptc_send(ERROR_PARAMETERS, "Too long user name.",
        client->_fd, &myServ->writefds);
        return true;
    }
    return false;
}

static user_t *get_user_data(server_t *myServ, char *user_name)
{
    user_t *tmp = myServ->_list_users->first;

    while (tmp) {
        if (strcmp(tmp->username, user_name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

static void display_login(client_t *client, server_t *myServ)
{
    client_t *tmp = myServ->_list_client->first;

    while (tmp) {
        if (tmp->_user_data)
            dprintf(tmp->_fd, "%i \"%s\" \"%s\"\r\n", CLIENT_EVENT_LOGGED_IN,
            client->_user_data->uuid, client->_user_data->username);
        tmp = tmp->_next;
    }
}

static void login_client(char **command, server_t *myServ, client_t *client)
{
    char *uuid = create_uuid();

    if (is_user_name_too_long(command, client, myServ))
        return;
    client->_user_data = get_user_data(myServ, command[1]);
    if (client->_user_data != NULL) {
        server_event_user_logged_in(client->_user_data->uuid);
        display_login(client, myServ);
        return;
    }
    if (!uuid)
        return;
    client->_user_data = create_user(myServ->_list_users, uuid, command[1]);
    free(uuid);
    if (!client->_user_data)
        return;
    server_event_user_created(client->_user_data->uuid,
    client->_user_data->username);
    server_event_user_logged_in(client->_user_data->uuid);
    display_login(client, myServ);
}

void login_command(char **command, server_t *myServ, client_t *client)
{
    if (!is_correct_command(&myServ->writefds, command, 1, client->_fd))
        return;
    if (client->_user_data) {
        ptc_send(LOGGED_IN, "User logged in, proceed.",
        client->_fd, &myServ->writefds);
        return;
    }
    login_client(command, myServ, client);
}
