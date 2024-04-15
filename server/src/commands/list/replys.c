/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** replys
*/

#include "types.h"
#include "utils.h"
#include "protocol.h"

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

static bool check_thread(thread_t *thread, int fd, char *uuid)
{
    if (!thread) {
        dprintf(fd, "%d \"%s\"\r\n", CLIENT_ERROR_UNKNOWN_THREAD, uuid);
        return false;
    }
    return true;
}

static bool all_set(client_t *client, server_t *server)
{
    char *team_uuid = client->_use_uuid_team;
    char *channel_uuid = client->_use_uuid_channel;
    char *thread_uuid = client->_use_uuid_thread;
    team_t *team = team_get_by_uuid(team_uuid, server->_list_teams);
    channel_t *channel = NULL;
    thread_t *thread = NULL;

    if (!team) {
        dprintf(client->_fd, "%d \"%s\"\r\n", CLIENT_ERROR_UNKNOWN_TEAM,
            team_uuid);
        return false;
    }
    channel = channel_get_by_uuid(channel_uuid, team->channels);
    if (!channel) {
        dprintf(client->_fd, "%d \"%s\"\r\n", CLIENT_ERROR_UNKNOWN_CHANNEL,
            channel_uuid);
        return false;
    }
    thread = thread_get_by_uuid(thread_uuid, channel->threads);
    return check_thread(thread, client->_fd, thread_uuid);
}

void print_replys(server_t *server, client_t *client)
{
    char *team_uuid = client->_use_uuid_team;
    char *channel_uuid = client->_use_uuid_channel;
    char *thread_uuid = client->_use_uuid_thread;
    team_t *team = NULL;
    channel_t *channel = NULL;
    thread_t *thread = NULL;

    if (!all_set(client, server))
        return;
    team = team_get_by_uuid(team_uuid, server->_list_teams);
    channel = channel_get_by_uuid(channel_uuid, team->channels);
    thread = thread_get_by_uuid(thread_uuid, channel->threads);
    print_list_all_comments(thread, client->_fd, &server->writefds);
}
