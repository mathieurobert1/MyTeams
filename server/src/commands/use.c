/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** use
*/

#include "types.h"
#include "utils.h"
#include "commands.h"
#include "protocol.h"

void use_command(char **command, server_t *myServ, client_t *client)
{
    if (command[1] == NULL) {
        change_use(EMPTY, NULL, client);
        ptc_send(COMMAND_SUCCESS, "Command succes",
        client->_fd, &myServ->writefds);
        return;
    }
    if (!is_correct_command(&myServ->writefds, command, 1, client->_fd))
        return;
    if (uuid_is_team(command[1], myServ, client))
        return;
    ptc_send(ERROR_PARAMETERS, "Error uuid not found.",
    client->_fd, &myServ->writefds);
}
