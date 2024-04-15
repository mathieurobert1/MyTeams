/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** info
*/

#include "types.h"
#include "utils.h"  // *
#include "commands.h"   // use_command_e
#include "protocol.h"   // ptc_send

#include <string.h>     // strlen
#include <stdlib.h>     // malloc
#include <stdio.h>

static void print_info_user(user_t *user, int fd, fd_set *write_fds)
{
    if (FD_ISSET(fd, write_fds))
        dprintf(fd, "User: username: %s, uuid: %s\n",
            user->username, user->uuid);
}

static void print_info_team(team_t *team, int fd, fd_set *write_fds)
{
    if (FD_ISSET(fd, write_fds))
        dprintf(fd, "Team: uuid: %s, name: %s, description: %s\n",
            team->uuid, team->name, team->description);
}

static void print_info_channel(channel_t *channel, int fd, fd_set *write_fds)
{
    if (FD_ISSET(fd, write_fds))
        dprintf(fd, "Channel: uuid: %s, name: %s, description: %s\n",
            channel->uuid, channel->name, channel->description);
}

static void print_info_thread(thread_t *thread, int fd, fd_set *write_fds)
{
    if (FD_ISSET(fd, write_fds))
        dprintf(fd, "Thread: uuid: %s, title: %s, content: %s\n",
            thread->uuid, thread->title, thread->content);
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
        print_info_team(team, client->_fd, write_fds);
    if (client->_use_state == CHANNEL)
        print_info_channel(channel, client->_fd, write_fds);
    if (client->_use_state == THREAD)
        print_info_thread(thread, client->_fd, write_fds);
}

void info_command(char **command, server_t *myServ, client_t *client)
{
    char *str = NULL;

    if (!is_correct_command(&myServ->writefds, command, 0, client->_fd))
        return;
    if (!is_context_def(client->_fd, &myServ->writefds, client->_use_state))
        return;
    print_info(client, myServ, &myServ->writefds);
}
