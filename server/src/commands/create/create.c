/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** create
*/

#include "types.h"
#include "commands.h"
#include "protocol.h"
#include "utils.h"
#include "lists.h"

#include <string.h>

void create_command(char **command, server_t *myServ, client_t *client)
{
    if (client->_use_state == NONE) {
        ptc_send(NO_CONTEXT, "No context defined before: /use",
        client->_fd, &myServ->writefds);
        return;
    }
    if (client->_use_state == EMPTY)
        return create_new_team(command, myServ, client);
    if (client->_use_state == TEAM)
        return create_new_channel(command, myServ, client);
    if (client->_use_state == CHANNEL)
        return create_new_thread(command, myServ, client);
    // if (client->_use_state == THREAD)
    //     return create_new_message(command, myServ, client);
}
