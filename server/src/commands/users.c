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
#include <stdio.h>

static void print_message(user_list_t *user_list, client_t *client,
    server_t *server)
{
    user_t *tmp = user_list->first;

    while (tmp != NULL) {
        if (FD_ISSET(client->_fd, &server->writefds))
            dprintf(client->_fd, "%d \"%s\" \"%s\" \"%d\"\r\n",
                CLIENT_PRINT_USERS, tmp->uuid, tmp->username, tmp->is_logged);
        tmp = tmp->next;
    }
}

void users_command(char **command, server_t *myServ, client_t *client)
{
    user_list_t *user_list = myServ->_list_users;

    if (is_correct_command(&myServ->writefds,
    command, 0, client->_fd) == false)
        return;
    print_message(user_list, client, myServ);
}
