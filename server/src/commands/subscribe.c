/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** subscribe
*/

#include "types.h"
#include "utils.h"
#include "protocol.h"
#include "lists.h"
#include "logging_server.h"

#include <unistd.h>
#include <stdio.h>

void subscribe_command(char **command, server_t *myServ, client_t *client)
{
    team_t *team = NULL;

    if (!is_correct_command(&myServ->writefds, command, 1, client->_fd))
        return;
    team = team_get_by_uuid(command[1], myServ->_list_teams);
    if (!team) {
        ptc_send(CLIENT_ERROR_UNKNOWN_TEAM, command[1],
        client->_fd, &myServ->writefds);
        return;
    }
    add_to_list_users(team->users, client->_user_data);
    server_event_user_subscribed(command[1], client->_user_data->uuid);
    if (FD_ISSET(client->_fd, &myServ->writefds))
        dprintf(client->_fd, "%i \"%s\" \"%s\"\r\n", CLIENT_PRINT_SUBSCRIBED,
        client->_user_data->uuid, command[1]);
}
