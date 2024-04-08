/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** login
*/

#include "types.h"
#include "protocol.h"
#include "commands.h"

void login_command(char **command, server_t *myServ, client_t *client)
{
    if (is_correct_command(&myServ->writefds,
    command, 1, client->_fd))
        return;
}
