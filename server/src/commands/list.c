/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list
*/

#include "types.h"
#include "utils.h"  // *
#include "commands.h"   // use_command_e
#include "protocol.h"   // ptc_send

static channel_list_t *get_channel_list(char *team_uuid, server_t *myServ)
{
    team_t *team = team_get_by_uuid(team_uuid, myServ->_list_teams);

    if (!team)
        return NULL;
    return team->channels;
}

static thread_list_t *get_thread_list(server_t *myServ, char *team_uuid,
    char *channel_uuid)
{
    team_t *team = team_get_by_uuid(team_uuid, myServ->_list_teams);
    channel_t *channel = NULL;

    if (!team)
        return NULL;
    channel = channel_get_by_uuid(channel_uuid, team->channels);
    if (!channel)
        return NULL;
    return channel->threads;
}

static thread_t *get_thread(server_t *myServ, char *team_uuid,
    char *channel_uuid, char *thread_uuid)
{
    team_t *team = team_get_by_uuid(team_uuid, myServ->_list_teams);
    channel_t *channel = NULL;
    thread_t *thread = NULL;

    if (!team)
        return NULL;
    channel = channel_get_by_uuid(channel_uuid, team->channels);
    if (!channel)
        return NULL;
    thread = thread_get_by_uuid(thread_uuid, channel->threads);
    if (!thread)
        return NULL;
    return thread;
}

static void list_print(client_t *client, server_t *myServ)
{
    channel_list_t *channels = get_channel_list(client->_use_uuid_team,
        myServ);
    thread_list_t *threads = get_thread_list(myServ, client->_use_uuid_team,
            client->_use_uuid_channel);
    thread_t *thread = get_thread(myServ, client->_use_uuid_team,
        client->_use_uuid_channel, client->_use_uuid_thread);

    if (client->_use_state == EMPTY)
        print_list_all_teams(myServ->_list_teams, client->_fd,
            &myServ->writefds);
    if (client->_use_state == TEAM)
        print_list_all_channels(channels, client->_fd, &myServ->writefds);
    if (client->_use_state == CHANNEL)
        print_list_all_threads(threads, client->_fd, &myServ->writefds);
    if (client->_use_state == THREAD)
        print_list_all_comments(thread, client->_fd, &myServ->writefds);
}

void list_command(char **command, server_t *myServ, client_t *client)
{
    if (!is_correct_command(&myServ->writefds, command, 0, client->_fd))
        return;
    if (!is_context_def(client->_fd, &myServ->writefds, client->_use_state))
        return;
    list_print(client, myServ);
}
