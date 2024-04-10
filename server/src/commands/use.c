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

static int len_tab(char **tab)
{
    int len = 0;

    for (int i = 0; tab[i] != NULL; i++)
        len++;
    return len;
}

void use_command(char **command, server_t *myServ, client_t *client)
{
    if (command[1] == NULL) {
        change_use(EMPTY, NULL, client);
        ptc_send(COMMAND_SUCCESS, "Command succes",
        client->_fd, &myServ->writefds);
        return;
    }
    if (len_tab(command) > 4) {
        ptc_send(TOO_MORE_PARAMETERS, "Too more parameters.",
        client->_fd, &myServ->writefds);
        return;
    }
    if (uuid_is_team(command, myServ, client)) {
        ptc_send(COMMAND_SUCCESS, "Command succes",
        client->_fd, &myServ->writefds);
        return;
    }
    ptc_send(ERROR_PARAMETERS, "Error in uuid(s) not found.",
    client->_fd, &myServ->writefds);
}
