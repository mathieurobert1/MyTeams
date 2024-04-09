/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** channel
*/

#include "types.h"  // channel_t, channel_list_t
#include "lists.h"  // add_channel_to_list
#include "data.h"   // deserialize_thread_list, deserialize_string

#include <unistd.h> // read
#include <stdlib.h> // malloc

channel_t *deserialize_channel(int fd)
{
    channel_t *channel = malloc(sizeof(channel_t));

    if (!channel)
        return NULL;
    read(fd, channel, sizeof(channel_t));
    channel->uuid = deserialize_string(fd);
    channel->name = deserialize_string(fd);
    channel->description = deserialize_string(fd);
    channel->threads = deserialize_thread_list(fd);
    channel->next = NULL;
    channel->last = NULL;
    return channel;
}

channel_list_t *deserialize_channel_list(int fd)
{
    channel_list_t *list = malloc(sizeof(channel_list_t));
    channel_t *tmp = NULL;
    int tmp_nb_channel = 0;

    if (!list)
        return NULL;
    read(fd, list, sizeof(channel_list_t));
    list->first = NULL;
    list->last = NULL;
    tmp_nb_channel = list->nb_channel;
    list->nb_channel = 0;
    for (int i = 0; tmp_nb_channel; i++) {
        tmp = deserialize_channel(fd);
        if (!tmp)
            return NULL;
        add_to_list_channel(list, tmp);
    }
    return list;
}
