/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** list channels
*/

#include "types.h"
#include <stdlib.h>
#include <unistd.h>

channel_list_t *init_list_channels(void)
{
    channel_list_t *channel_list = malloc(sizeof(channel_list_t));

    if (!channel_list)
        return NULL;
    channel_list->first = NULL;
    channel_list->last = NULL;
    channel_list->nb_channel = 0;
    return channel_list;
}

channel_t *create_channel(channel_list_t *list_channels, char *name, char *uuid)
{
    channel_t *channel = malloc(sizeof(channel_t));

    if (!channel)
        return NULL;
    channel->last = NULL;
    channel->next = NULL;
    channel->name = strdup(name);
    channel->uuid = strdup(uuid);
    channel->description = NULL;
    channel->threads = NULL;
    return channel;
}

void delete_channel(channel_t *channel)
{
    if (!channel)
        return;
    if (channel->name)
        free(channel->name);
    if (channel->uuid)
        free(channel->uuid);
    if (channel->description)
        free(channel->description);
    free(channel);
}

void delete_list_channels(channel_list_t *list_channels)
{
    channel_t *tmp = NULL;
    channel_t *tmp2 = NULL;

    if (!list_channels)
        return;
    tmp = list_channels->first;
    while (tmp) {
        tmp2 = tmp->next;
        delete_channel(tmp);
        tmp = tmp2;
    }
    free(list_channels);
}

void add_to_list_channel(channel_list_t *list, channel_t *channel)
{
    client_t *tmp = list->first;

    if (list->nb_channel == 0) {
        list->first = channel;
        list->last = channel;
        channel->last = NULL;
        channel->next = NULL;
        list->nb_channel++;
        return;
    }
    list->first = channel;
    channel->last = NULL;
    tmp->_last = channel;
    channel->next = tmp;
    list->nb_channel++;
}
