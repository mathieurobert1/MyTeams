/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** handle_response
*/
#include "client.h"
#include "shared.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "logging_client.h"
#include "protocol.h"

static void handles1(int code, char **parsed, client_t *client)
{
    if (code == CLIENT_EVENT_LOGGED_IN) {
        client_event_logged_in(parsed[1], parsed[2]);
        client->user_uuid = strdup(parsed[1]);
        client->user_name = strdup(parsed[2]);
    }
    if (code == CLIENT_EVENT_LOGGED_OUT)
        client_event_logged_out(parsed[1], parsed[2]);
    if (code == CLIENT_EVENT_PRIVATE_MESSAGE_RECEIVED)
        client_event_private_message_received(parsed[1], parsed[2]);
    if (code == CLIENT_EVENT_THREAD_REPLY_RECEIVED)
        client_event_thread_reply_received(parsed[1],
            parsed[2], parsed[3], parsed[4]);
    if (code == CLIENT_EVENT_TEAM_CREATED)
        client_event_team_created(parsed[1], parsed[2], parsed[3]);
    if (code == CLIENT_EVENT_CHANNEL_CREATED)
        client_event_channel_created(parsed[1], parsed[2], parsed[3]);
    if (code == CLIENT_EVENT_THREAD_CREATED)
        client_event_thread_created(parsed[1], parsed[2],
            (long int) atoi(parsed[3]), parsed[4], parsed[5]);
}

static void handles2(int code, char **parsed, client_t *client)
{
    (void) client;
    if (code == CLIENT_PRINT_USERS)
        client_print_users(parsed[1], parsed[2], atoi(parsed[3]));
    if (code == CLIENT_PRINT_TEAMS)
        client_print_teams(parsed[1], parsed[2], parsed[3]);
    if (code == CLIENT_TEAM_PRINT_CHANNELS)
        client_team_print_channels(parsed[1], parsed[2], parsed[3]);
    if (code == CLIENT_CHANNEL_PRINT_THREADS)
        client_channel_print_threads(parsed[1], parsed[2],
            (long int) atoi(parsed[3]), parsed[4], parsed[5]);
    if (code == CLIENT_THREAD_PRINT_REPLIES)
        client_thread_print_replies(parsed[1], parsed[2],
            (long int) atoi(parsed[3]), parsed[4]);
    if (code == CLIENT_PRIVATE_MESSAGE_PRINT_MESSAGES)
        client_private_message_print_messages(parsed[1],
            (long int) atoi(parsed[2]), parsed[3]);
    if (code == CLIENT_ERROR_UNKNOWN_TEAM)
        client_error_unknown_team(parsed[1]);
    if (code == CLIENT_ERROR_UNKNOWN_CHANNEL)
        client_error_unknown_channel(parsed[1]);
}

static void handles3(int code, char **parsed, client_t *client)
{
    (void) client;
    if (code == CLIENT_ERROR_UNKNOWN_THREAD)
        client_error_unknown_thread(parsed[1]);
    if (code == CLIENT_ERROR_UNKNOWN_USER)
        client_error_unknown_user(parsed[1]);
    if (code == CLIENT_ERROR_UNAUTHORIZED)
        client_error_unauthorized();
    if (code == CLIENT_ERROR_ALREADY_EXIST)
        client_error_already_exist();
    if (code == CLIENT_PRINT_USER)
        client_print_user(parsed[1], parsed[2], atoi(parsed[3]));
    if (code == CLIENT_PRINT_TEAM)
        client_print_team(parsed[1], parsed[2], parsed[3]);
    if (code == CLIENT_PRINT_CHANNEL)
        client_print_channel(parsed[1], parsed[2], parsed[3]);
    if (code == CLIENT_PRINT_THREAD)
        client_print_thread(parsed[1], parsed[2],
            (long int) atoi(parsed[3]), parsed[4], parsed[5]);
    if (code == CLIENT_PRINT_TEAM_CREATED)
        client_print_team_created(parsed[1], parsed[2], parsed[3]);
}

static void handles4(int code, char **parsed, client_t *client)
{
    (void) client;
    if (code == CLIENT_PRINT_CHANNEL_CREATED)
        client_print_channel_created(parsed[1], parsed[2], parsed[3]);
    if (code == CLIENT_PRINT_THREAD_CREATED)
        client_print_thread_created(parsed[1], parsed[2],
            (long int) atoi(parsed[3]), parsed[4], parsed[5]);
    if (code == CLIENT_PRINT_REPLY_CREATED)
        client_print_reply_created(parsed[1], parsed[2],
            (long int) atoi(parsed[3]), parsed[4]);
    if (code == CLIENT_PRINT_SUBSCRIBED)
        client_print_subscribed(parsed[1], parsed[2]);
    if (code == CLIENT_PRINT_UNSUBSCRIBED)
        client_print_subscribed(parsed[1], parsed[2]);
}

void handle_response(client_t *client, char *msg)
{
    char **parsed = get_list_arg(msg);
    int code = atoi(parsed[0]);

    handles1(code, parsed, client);
    handles2(code, parsed, client);
    handles3(code, parsed, client);
    handles4(code, parsed, client);
    write(1, msg, strlen(msg));
    delete_list_arg(parsed);
}
