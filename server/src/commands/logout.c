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

void logout_command(char **command, server_t *myServ, client_t *client)
{
    if (is_too_more_args(command, 0, client->_fd, &myServ->writefds))
        return;
    server_event_user_logged_out(client->_user_data->uuid);
    ptc_send(LOGED_OUT, "Service closing control connection."
    " Logged out if appropriate.", client->_fd, &myServ->writefds);
    delete_a_client(client, myServ);
}
