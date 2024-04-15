/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** create Thread
*/

#include "types.h"
#include "utils.h"
#include "protocol.h"
#include "lists.h"
#include "commands.h"
#include "logging_server.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

static char *get_message_for_clients(char *uuid, time_t ltime, char **command,
    char *message)
{
    strcat(message, uuid);
    strcat(message, "\" \"");
    strcat(message, ctime(&ltime));
    strcat(message, "\" \"");
    strcat(message, command[1]);
    strcat(message, "\" \"");
    strcat(message, command[2]);
    strcat(message, "\"");
    return message;
}

static char *get_message_create_thread(char *uuid, char **command,
    int code, user_t *user)
{
    time_t ltime;
    size_t len = strlen(uuid) + strlen(user->uuid) +
    strlen(command[1]) + strlen(command[2]) + 15;
    char *message = NULL;

    time(&ltime);
    len += strlen(ctime(&ltime));
    message = malloc(sizeof(char) * (len + 1));
    if (!message)
        return NULL;
    memset(message, 0, len + 1);
    strcat(message, int_to_char(code));
    strcat(message, " \"");
    strcat(message, uuid);
    strcat(message, "\" \"");
    return get_message_for_clients(user->uuid, ltime, command, message);
}

static bool is_thread_name_exist(thread_list_t *list, char *name,
    client_t *client, server_t *myServ)
{
    thread_t *thread = list->first;

    while (thread) {
        if (strcmp(thread->title, name) == 0) {
            ptc_send(CLIENT_ERROR_ALREADY_EXIST, "",
            client->_fd, &myServ->writefds);
            return true;
        }
        thread = thread->next;
    }
    return false;
}

static void send_create_thread_message(char **command, char *uuid,
    server_t *myServ, client_t *client)
{
    char *msg = get_message_create_thread(uuid, command,
    CLIENT_PRINT_THREAD_CREATED,
    client->_user_data);
    char *msg_all = get_message_create_thread(uuid, command,
    CLIENT_EVENT_THREAD_CREATED,
    client->_user_data);

    if (!msg)
        return;
    if (!msg_all) {
        free(msg);
        return;
    }
    if (FD_ISSET(client->_fd, &myServ->writefds))
        dprintf(client->_fd, "%s\r\n", msg);
    send_to_all_clients(client, myServ, msg_all);
    free(msg);
    free(msg_all);
}

static void create_new_thread_next(char **command, server_t *myServ,
    client_t *client, team_t *team)
{
    user_t *user = NULL;
    channel_t *channel = channel_get_by_uuid(client->_use_uuid_channel,
    team->channels);
    char *uuid = create_uuid();

    user = user_get_by_uuid(client->_user_data->uuid, team->users);
    if (!user) {
        ptc_send(CLIENT_ERROR_UNKNOWN_TEAM, client->_use_uuid_team,
        client->_fd, &myServ->writefds);
        return;
    }
    if (is_thread_name_exist(channel->threads, command[1], client, myServ))
        return;
    if (!uuid)
        return;
    create_thread(channel->threads, uuid, command[1], command[2]);
    server_event_thread_created(channel->uuid, uuid, client->_user_data->uuid,
    command[1], command[2]);
    send_create_thread_message(command, uuid, myServ, client);
    free(uuid);
}

void create_new_thread(char **command, server_t *myServ, client_t *client)
{
    team_t *team = NULL;
    channel_t *channel = NULL;

    if (!is_no_error(command, myServ, client, MAX_BODY_LENGTH))
        return;
    if (!client->_use_uuid_team || !client->_use_uuid_channel)
        return;
    team = team_get_by_uuid(client->_use_uuid_team, myServ->_list_teams);
    if (!team) {
        ptc_send(CLIENT_ERROR_UNKNOWN_TEAM, client->_use_uuid_team,
        client->_fd, &myServ->writefds);
        return;
    }
    channel = channel_get_by_uuid(client->_use_uuid_channel, team->channels);
    if (!channel) {
        ptc_send(CLIENT_ERROR_UNKNOWN_CHANNEL, client->_use_uuid_channel,
        client->_fd, &myServ->writefds);
        return;
    }
    create_new_thread_next(command, myServ, client, team);
}
