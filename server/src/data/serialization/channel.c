/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** channel
*/

#include "types.h"  // channel_t, channel_list_t
#include "data.h"   // serialize_thread_list, serialize_string

#include <unistd.h> // write

void serialize_channel(int fd, channel_t *channel)
{
    write(fd, channel, sizeof(channel_t));
    serialize_string(fd, channel->uuid);
    serialize_string(fd, channel->name);
    serialize_string(fd, channel->description);
    serialize_thread_list(fd, channel->threads);
}

void serialize_channel_list(int fd, channel_list_t *list)
{
    channel_t *tmp = list->first;

    write(fd, list, sizeof(channel_list_t));
    while (tmp) {
        serialize_channel(fd, tmp);
        tmp = tmp->next;
    }
}
