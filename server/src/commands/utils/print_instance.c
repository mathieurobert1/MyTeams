/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list_instance
*/

#include "types.h" // *
#include "protocol.h" // *

#include <stddef.h> // null
#include <string.h> // strcmp
#include <stdlib.h> // malloc
#include <stdio.h> // dprintf

void print_list_all_teams(team_list_t *teams, int fd, fd_set *writefds)
{
    team_t *tmp = teams->first;

    if (tmp == NULL && FD_ISSET(fd, writefds))
        dprintf(fd, "%d\r\n", COMMAND_SUCCESS);
    while (tmp) {
        if (FD_ISSET(fd, writefds) == 0)
            return;
        dprintf(fd, "%d \"%s\" \"%s\"\r\n", CLIENT_PRINT_TEAM, tmp->uuid,
            tmp->name);
        tmp = tmp->next;
    }
}

void print_list_all_threads(thread_list_t *threads, int fd, fd_set *writefds)
{
    thread_t *tmp = threads->first;

    if (tmp == NULL)
        dprintf(fd, "%d\r\n", COMMAND_SUCCESS);
    while (tmp) {
        if (FD_ISSET(fd, writefds) == 0)
            return;
        dprintf(fd, "%d \"%s\" \"%s\" \"%s\"\r\n", CLIENT_PRINT_THREAD,
            tmp->uuid, tmp->title, tmp->content);
        tmp = tmp->next;
    }
}

void print_list_all_channels(channel_list_t *channels, int fd,
    fd_set *writefds)
{
    channel_t *tmp = channels->first;

    if (tmp == NULL)
        dprintf(fd, "%d\r\n", COMMAND_SUCCESS);
    while (tmp) {
        if (FD_ISSET(fd, writefds) == 0)
            return;
        dprintf(fd, "%d \"%s\" \"%s\"\r\n", CLIENT_PRINT_CHANNEL, tmp->uuid,
            tmp->name);
        tmp = tmp->next;
    }
}

void print_list_all_comments(thread_t *thread, int fd, fd_set *writefds)
{
    comment_list_t *comments = thread->comments;
    comment_t *tmp = comments->first;

    if (tmp == NULL)
        dprintf(fd, "%d\r\n", COMMAND_SUCCESS);
    while (tmp) {
        if (FD_ISSET(fd, writefds) == 0)
            return;
        dprintf(fd, "%d \"%s\" \"%s\" \"%ld\", \"%s\"\r\n",
            CLIENT_THREAD_PRINT_REPLIES, thread->uuid, tmp->uuid,
            tmp->timestamp, tmp->content);
        tmp = tmp->next;
    }
}
