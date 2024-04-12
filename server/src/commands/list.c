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

static thread_list_t *get_thread_list(server_t *myServ, char *team_uuid, char *channel_uuid)
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

static comment_list_t *get_comment_list(server_t *myServ, char *team_uuid, char *channel_uuid, char *thread_uuid)
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
    return thread->comments;
}

void list_command(char **command, server_t *myServ, client_t *client)
{
    char *str = NULL;
    channel_list_t *channels = NULL;
    thread_list_t *threads = NULL;
    comment_list_t *comments = NULL;

    if (!is_correct_command(&myServ->writefds, command, 0, client->_fd))
        return;
    if (client->_use_state == NULL) {
        ptc_send(NOT_CONTEXT, "You must be in a team, channel or thread to use this command", client->_fd, &myServ->writefds);
        return;
    } if (client->_use_state == EMPTY) {
        str = get_str_list_all_teams(myServ->_list_teams);
    } if (client->_use_state == TEAM) {
        channels = get_channel_list(client->_use_uuid_team, myServ);
        str = get_str_list_all_channels(channels);
    } if (client->_use_state == CHANNEL) {
        threads = get_thread_list(myServ, client->_use_uuid_team, client->_use_uuid_channel);
        str = get_str_list_all_threads(threads);
    } if (client->_use_state == THREAD) {
        comments = get_comment_list(myServ, client->_use_uuid_team, client->_use_uuid_channel, client->_use_uuid_thread);
        str = get_str_list_all_comments(comments);
    }
    ptc_send(COMMAND_SUCCESS, str, client->_fd, &myServ->writefds);
}
