/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** info
*/

#include "types.h"
#include "utils.h"  // *
#include "commands.h"   // use_command_e
#include "protocol.h"   // *

#include <string.h>     // strlen
#include <stdlib.h>     // malloc
#include <stdio.h>

static void print_info_user(user_t *user, int fd, fd_set *write_fds)
{
    if (FD_ISSET(fd, write_fds))
        dprintf(fd, "%d \"%s\" \"%s\" \"1\"\r\n", CLIENT_PRINT_USER,
            user->uuid, user->username);
}

static void print_info_team(team_t *team, int fd, fd_set *write_fds,
    char *uuid)
{
    if (team == NULL) {
        if (FD_ISSET(fd, write_fds)) {
            dprintf(fd, "%d \"%s\"\r\n", CLIENT_ERROR_UNKNOWN_TEAM, uuid);
        }
        return;
    }
    if (FD_ISSET(fd, write_fds)) {
        dprintf(fd, "%d \"%s\" \"%s\" \"%s\"\r\n",
            CLIENT_PRINT_TEAM, team->uuid, team->name, team->description);
    }
}

static void print_info_channel(channel_t *channel, int fd, fd_set *write_fds,
    char *uuid)
{
    if (channel == NULL) {
        if (FD_ISSET(fd, write_fds)) {
            dprintf(fd, "%d \"%s\"\r\n", CLIENT_ERROR_UNKNOWN_CHANNEL, uuid);
        }
        return;
    }
    if (FD_ISSET(fd, write_fds)) {
        dprintf(fd, "%d \"%s\" \"%s\" \"%s\"\r\n", CLIENT_PRINT_CHANNEL,
            channel->uuid, channel->name, channel->description);
    }
}

static void print_info_thread(thread_t *thread, int fd, fd_set *write_fds,
    char *uuid)
{
    if (thread == NULL) {
        if (FD_ISSET(fd, write_fds)) {
            dprintf(fd, "%d \"%s\"\r\n", CLIENT_ERROR_UNKNOWN_THREAD, uuid);
        }
        return;
    }
    if (FD_ISSET(fd, write_fds))
        dprintf(fd, "%d \"%s\" \"%s\" \"%ld\" \"%s\" \"%s\"\r\n",
            CLIENT_PRINT_THREAD, thread->uuid, thread->author->uuid,
            thread->timestamp, thread->title, thread->content);
}

static void print_info(client_t *client, server_t *myServ, fd_set *write_fds)
{
    team_t *team = team_get_by_uuid(client->_use_uuid_team,
        myServ->_list_teams);
    channel_t *channel = channel_get_by_uuid(client->_use_uuid_channel,
        team->channels);
    thread_t *thread = thread_get_by_uuid(client->_use_uuid_thread,
        channel->threads);

    if (client->_use_state == EMPTY)
        print_info_user(client->_user_data, client->_fd, write_fds);
    if (client->_use_state == TEAM)
        print_info_team(team, client->_fd, write_fds, client->_use_uuid_team);
    if (client->_use_state == CHANNEL)
        print_info_channel(channel, client->_fd, write_fds,
            client->_use_uuid_channel);
    if (client->_use_state == THREAD)
        print_info_thread(thread, client->_fd, write_fds,
            client->_use_uuid_thread);
}

void info_command(char **command, server_t *myServ, client_t *client)
{
    if (!is_correct_command(&myServ->writefds, command, 0, client->_fd))
        return;
    if (!is_context_def(client->_fd, &myServ->writefds, client->_use_state))
        return;
    print_info(client, myServ, &myServ->writefds);
}
