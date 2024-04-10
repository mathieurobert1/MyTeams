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
    if (use_state == TEAM) {
        if (client->_use_uuid_team)
            free(client->_use_uuid_team);
        client->_use_uuid_team = uuid;
    }
    if (use_state == CHANNEL) {
        if (client->_use_uuid_channel)
            free(client->_use_uuid_channel);
        client->_use_uuid_channel = uuid;
    }
    if (use_state == THREAD) {
        if (client->_use_uuid_thread)
            free(client->_use_uuid_thread);
        client->_use_uuid_thread = uuid;
    }
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

static bool uuid_is_thread(char *uuid, channel_t *channel, client_t *client)
{
    thread_t *thread = channel->threads->first;

    while (thread) {
        if (strcmp(thread->uuid, uuid) == 0) {
            change_use(THREAD, strdup(uuid), client);
            return true;
        }
        thread = thread->next;
    }
    return false;
}

static bool uuid_is_channel(char **command, team_t *team, client_t *client)
{
    channel_t *channel = team->channels->first;
    bool find = false;

    while (channel) {
        if (strcmp(channel->uuid, command[2]) == 0) {
            change_use(CHANNEL, strdup(command[2]), client);
            find = true;
        }
        if (command[3] && find)
            return uuid_is_thread(command[3], channel, client);
        if (find)
            return true;
        channel = channel->next;
    }
    return false;
}

bool uuid_is_team(char **command, server_t *myServ, client_t *client)
{
    team_t *team = myServ->_list_teams->first;
    bool find = false;

    while (team) {
        if (strcmp(team->uuid, command[1]) == 0 &&
        user_is_in_team(client->_user_data->uuid, team)) {
            change_use(TEAM, strdup(command[1]), client);
            find = true;
        }
        if (find && command[2])
            return uuid_is_channel(command, team, client);
        if (find)
            return true;
        team = team->next;
    }
    return false;
}
