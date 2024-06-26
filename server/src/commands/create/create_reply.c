/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** create Reply
*/

#include "types.h"
#include "protocol.h"
#include "utils.h"
#include "lists.h"
#include "commands.h"
#include "logging_server.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

static bool is_error_unknown(server_t *myServ, client_t *client, team_t *team)
{
    channel_t *channel = NULL;
    thread_t *thread = NULL;

    channel = channel_get_by_uuid(client->_use_uuid_channel, team->channels);
    if (!channel) {
        ptc_send(CLIENT_ERROR_UNKNOWN_CHANNEL, client->_use_uuid_channel,
        client->_fd, &myServ->writefds);
        return true;
    }
    thread = thread_get_by_uuid(client->_use_uuid_thread, channel->threads);
    if (!thread) {
        ptc_send(CLIENT_ERROR_UNKNOWN_THREAD, client->_use_uuid_thread,
        client->_fd, &myServ->writefds);
        return true;
    }
    return false;
}

static char *get_message_reply_for_client(char *thread_uuid,
    comment_t *comment, int code)
{
    size_t len = strlen(thread_uuid) + strlen(comment->author_uuid) +
        strlen(comment->content) + 15;
    char *message = NULL;

    message = malloc(sizeof(char) * (len + 1 +
        strlen(ctime(&comment->timestamp))));
    if (!message)
        return NULL;
    memset(message, 0, len + 1);
    sprintf(message, "%d \"%s\" \"%s\" \"%s\" \"%s\"", code, thread_uuid,
        comment->author_uuid, ctime(&comment->timestamp), comment->content);
    return message;
}

static char *get_message_reply_for_all(char *team_uuid, int code,
    client_t *client, comment_t *comment)
{
    size_t len = strlen(team_uuid) + strlen(client->_use_uuid_thread) +
    strlen(client->_user_data->uuid) + strlen(comment->content) + 15;
    char *message = malloc(sizeof(char) * (len + 1));

    if (!message)
        return NULL;
    memset(message, 0, len + 1);
    sprintf(message, "%d \"%s\" \"%s\" \"%s\" \"%s\"", code, team_uuid,
        client->_use_uuid_thread, client->_user_data->uuid, comment->content);
    return message;
}

static void send_create_reply(comment_t *comment,
    server_t *myServ, client_t *client, thread_t *thread)
{
    char *msg = get_message_reply_for_client(thread->uuid, comment,
        CLIENT_PRINT_REPLY_CREATED);
    char *msg_all = get_message_reply_for_all(client->_use_uuid_team,
    CLIENT_EVENT_THREAD_REPLY_RECEIVED, client, comment);

    server_event_reply_created(thread->uuid,
    client->_user_data->uuid, comment->content);
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

static void create_new_reply_next(char **command, server_t *myServ,
    client_t *client, team_t *team)
{
    user_t *user = NULL;
    channel_t *channel = channel_get_by_uuid(client->_use_uuid_channel,
    team->channels);
    thread_t *thread = thread_get_by_uuid(client->_use_uuid_thread,
    channel->threads);
    comment_t *comment = NULL;

    user = user_get_by_uuid(client->_user_data->uuid, team->users);
    if (!user) {
        ptc_send(CLIENT_ERROR_UNKNOWN_TEAM, client->_use_uuid_team,
        client->_fd, &myServ->writefds);
        return;
    }
    comment = create_comment(thread->comments, command[1],
    client->_user_data->uuid);
    if (!comment)
        return;
    send_create_reply(comment, myServ, client, thread);
}

void create_new_reply(char **command, server_t *myServ, client_t *client)
{
    team_t *team = NULL;

    if (!is_correct_command(&myServ->writefds, command, 1, client->_fd))
        return;
    if (strlen(command[1]) > MAX_BODY_LENGTH) {
        ptc_send(ERROR_PARAMETERS, "Too long second args",
        client->_fd, &myServ->writefds);
        return;
    }
    if (!client->_use_uuid_team || !client->_use_uuid_channel ||
    !client->_use_uuid_thread)
        return;
    team = team_get_by_uuid(client->_use_uuid_team, myServ->_list_teams);
    if (!team) {
        ptc_send(CLIENT_ERROR_UNKNOWN_TEAM, client->_use_uuid_team,
        client->_fd, &myServ->writefds);
        return;
    }
    if (!is_error_unknown(myServ, client, team))
        create_new_reply_next(command, myServ, client, team);
}
