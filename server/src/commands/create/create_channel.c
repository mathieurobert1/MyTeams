/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** create Channel
*/

#include "types.h"
#include "protocol.h"
#include "utils.h"
#include "lists.h"
#include "commands.h"

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool is_no_error(char **command, server_t *myServ, client_t *client,
    size_t length)
{
    if (is_correct_command(&myServ->writefds, command, 2, client->_fd))
        return false;
    if (strlen(command[1]) > MAX_NAME_LENGTH) {
        ptc_send(ERROR_PARAMETERS, "Too long name.",
        client->_fd, &myServ->writefds);
        return false;
    }
    if (strlen(command[2]) > length) {
        ptc_send(ERROR_PARAMETERS, "Too long second args",
        client->_fd, &myServ->writefds);
        return false;
    }
    return true;
}

static bool is_channel_name_exist(channel_list_t *list, char *name,
    client_t *client, server_t *myServ)
{
    channel_t *channel = list->first;

    while (channel) {
        if (strcmp(channel->name, name) == 0) {
            ptc_send(CLIENT_ERROR_ALREADY_EXIST, "",
            client->_fd, &myServ->writefds);
            return true;
        }
        channel = channel->next;
    }
    return false;
}

void find_user_to_send(user_t *user, client_t *tmp,
    server_t *myServ, char *msg_all)
{
    while (user) {
        if (strcmp(user->uuid, tmp->_user_data->uuid) == 0 &&
        FD_ISSET(tmp->_fd, &myServ->writefds))
                dprintf(tmp->_fd, "%s\r\n", msg_all);
        user = user->next;
    }
}

void find_clients_to_send(client_t *client, server_t *myServ, char *msg_all)
{
    client_t *tmp = myServ->_list_client->first;
    user_t *user = NULL;
    team_t *team = team_get_by_uuid(client->_use_uuid_team,
    myServ->_list_teams);

    while (tmp) {
        if (!tmp->_user_data) {
            tmp = tmp->_next;
            continue;
        }
        user = team->users->first;
        find_user_to_send(user, tmp, myServ, msg_all);
        tmp = tmp->_next;
    }
}

static void send_create_channel_message(char **command, char *uuid,
    server_t *myServ, client_t *client)
{
    char *msg = get_message_create(uuid, command[1], command[2], "940");
    char *msg_all = get_message_create(uuid, command[1], command[2], "750");

    if (!msg)
        return;
    if (!msg_all) {
        free(msg);
        return;
    }
    if (FD_ISSET(client->_fd, &myServ->writefds))
        dprintf(client->_fd, "%s\r\n", msg);
    find_clients_to_send(client, myServ, msg_all);
    free(msg);
    free(msg_all);
}

static void create_new_channel_next(char **command, server_t *myServ,
    client_t *client, team_t *team)
{
    user_t *user = NULL;
    char *uuid = NULL;

    user = user_get_by_uuid(client->_user_data->uuid, team->users);
    if (!user) {
        ptc_send(CLIENT_ERROR_UNKNOWN_TEAM, client->_use_uuid_team,
        client->_fd, &myServ->writefds);
        return;
    }
    if (is_channel_name_exist(team->channels, command[1], client, myServ))
        return;
    uuid = create_uuid();
    if (!uuid)
        return;
    create_channel(team->channels, command[1], command[2], uuid);
    send_create_channel_message(command, uuid, myServ, client);
    free(uuid);
}

void create_new_channel(char **command, server_t *myServ, client_t *client)
{
    team_t *team = NULL;

    if (!is_no_error(command, myServ, client, MAX_DESCRIPTION_LENGTH))
        return;
    if (!client->_use_uuid_team)
        return;
    team = team_get_by_uuid(client->_use_uuid_team, myServ->_list_teams);
    if (!team) {
        ptc_send(CLIENT_ERROR_UNKNOWN_TEAM, client->_use_uuid_team,
        client->_fd, &myServ->writefds);
        return;
    }
    create_new_channel_next(command, myServ, client, team);
}
