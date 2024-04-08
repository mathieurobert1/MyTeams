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
    if (is_too_few_args(command, 1)) {
        ptc_send(TOO_FEW_PARAMETERS, "Too few arguments",
        client->_fd, &myServ->writefds);
        return;
    }
    if (is_too_more_args(command, 1)) {
        ptc_send(TO_MORE_PARAMETERS, "Too more arguments",
        client->_fd, &myServ->writefds);
        return;
    }
}
