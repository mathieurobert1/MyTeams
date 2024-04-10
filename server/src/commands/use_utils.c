/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** use utils
*/

#include "types.h"
#include "utils.h"
#include "commands.h"
#include "protocol.h"

#include <string.h>
#include <stdlib.h>

void change_use(int use_state, char *uuid, client_t *client)
{
    client->_use_state = use_state;
    if (client->_use_uuid)
        free(client->_use_uuid);
    client->_use_uuid = uuid;
}

static bool user_is_in_team(char *uuid, team_t *team)
{
    user_t *user = team->users->first;

    while (user) {
        if (strcmp(user->uuid, uuid) == 0)
            return true;
        user = user->next;
    }
    return false;
}

static bool uuid_is_thread(char *uuid, channel_t *channel,
    server_t *myServ, client_t *client)
{
    thread_t *thread = channel->threads->first;

    while (thread) {
        if (strcmp(thread->uuid, uuid) == 0) {
            change_use(THREAD, strdup(uuid), client);
            ptc_send(COMMAND_SUCCESS, "Command succes",
            client->_fd, &myServ->writefds);
            return true;
        }
        thread = thread->next;
    }
    return false;
}

static bool uuid_is_channel(char *uuid, team_t *team,
    server_t *myServ, client_t *client)
{
    channel_t *channel = team->channels->first;

    while (channel) {
        if (strcmp(channel->uuid, uuid) == 0) {
            change_use(CHANNEL, strdup(uuid), client);
            ptc_send(COMMAND_SUCCESS, "Command succes",
            client->_fd, &myServ->writefds);
            return true;
        }
        if (uuid_is_thread(uuid, channel, myServ, client))
            return true;
        channel = channel->next;
    }
    return false;
}

bool uuid_is_team(char *uuid, server_t *myServ, client_t *client)
{
    team_t *team = myServ->_list_teams->first;

    while (team) {
        if (strcmp(team->uuid, uuid) == 0 &&
        user_is_in_team(client->_user_data->uuid, team)) {
            change_use(TEAM, strdup(uuid), client);
            ptc_send(COMMAND_SUCCESS, "Command succes",
            client->_fd, &myServ->writefds);
            return true;
        }
        if (uuid_is_channel(uuid, team, myServ, client))
            return true;
        team = team->next;
    }
    return false;
}
