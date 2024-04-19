/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** threads
*/

#include "types.h"
#include "utils.h"
#include "protocol.h"

#include <stddef.h>
#include <stdio.h>

void print_threads(server_t *server, client_t *client)
{
    char *team_uuid = client->_use_uuid_team;
    char *channel_uuid = client->_use_uuid_channel;
    team_t *team = team_get_by_uuid(team_uuid, server->_list_teams);
    channel_t *channel = NULL;

    if (!team && FD_ISSET(client->_fd, &server->writefds)) {
        dprintf(client->_fd, "%d \"%s\"\r\n", CLIENT_ERROR_UNKNOWN_TEAM,
            team_uuid);
        return;
    }
    channel = channel_get_by_uuid(channel_uuid, team->channels);
    if (!channel && FD_ISSET(client->_fd, &server->writefds)) {
        dprintf(client->_fd, "%d \"%s\"\r\n", CLIENT_ERROR_UNKNOWN_CHANNEL,
            channel_uuid);
        return;
    }
    print_list_all_threads(channel->threads, client->_fd, &server->writefds);
}
