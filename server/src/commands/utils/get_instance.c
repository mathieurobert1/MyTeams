/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** get_instance
*/

#include "types.h" // *

#include <stddef.h>
#include <string.h>

#include <stdio.h>

team_t *team_get_by_uuid(char *uuid, team_list_t *teams)
{
    team_t *tmp = teams->first;

    while (tmp) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

user_t *user_get_by_uuid(char *uuid, user_list_t *users)
{
    user_t *tmp = users->first;

    while (tmp) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

channel_t *channel_get_by_uuid(char *uuid, channel_list_t *channels)
{
    channel_t *tmp = channels->first;

    while (tmp) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

thread_t *thread_get_by_uuid(char *uuid, thread_list_t *threads)
{
    thread_t *tmp = threads->first;

    while (tmp) {
        if (strcmp(tmp->uuid, uuid) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
