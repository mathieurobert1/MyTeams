/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** channel
*/

#include "types.h"
#include "utils.h"
#include "protocol.h"

#include <stdio.h>

void print_channels(server_t *server, client_t *client)
{
    char *team_uuid = client->_use_uuid_team;
    team_t *team = team_get_by_uuid(team_uuid, server->_list_teams);

    if (!team) {
        dprintf(client->_fd, "%d \"%s\"\r\n", CLIENT_ERROR_UNKNOWN_TEAM,
            team_uuid);
        return;
    }
    print_list_all_channels(team->channels, client->_fd, &server->writefds);
}
