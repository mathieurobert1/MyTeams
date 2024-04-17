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
#include <stdio.h>

static void print_details(user_t *user, client_t *client)
{
    dprintf(client->_fd, "%d \"%s\" \"%s\" \"%d\"\r\n", CLIENT_PRINT_USER,
        user->uuid, user->username, user->is_logged);
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
        print_details(user, client);
    }
}
