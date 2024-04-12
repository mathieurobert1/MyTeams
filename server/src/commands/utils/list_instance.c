/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list_instance
*/

#include "types.h" // *

#include <stddef.h> // null
#include <string.h> // strcmp
#include <stdlib.h> // malloc

static int get_size_list_teams(team_list_t *teams)
{
    int size = 0;
    team_t *tmp = teams->first;

    while (tmp) {
        size += strlen(tmp->name) + 2 + strlen(tmp->uuid) + 3;
        tmp = tmp->next;
    }
    return size;
}

char *get_str_list_all_teams(team_list_t *teams)
{
    int size = get_size_list_teams(teams);
    char *str = malloc(sizeof(char) * (size + 3));
    team_t *tmp = teams->first;

    if (!str)
        return NULL;
    memset(str, 0, size + 3);
    strcat(str, "[");
    while (tmp) {
        strcat(str, tmp->name);
        strcat(str, ": ");
        strcat(str, tmp->uuid);
        strcat(str, ", ");
        tmp = tmp->next;
    }
    strcat(str, "]");
    return str;
}

static int get_size_list_threads(thread_list_t *threads)
{
    int size = 0;
    thread_t *tmp = threads->first;

    while (tmp) {
        size += strlen(tmp->title) + 2 + strlen(tmp->uuid) + 3;
        tmp = tmp->next;
    }
    return size;
}

char *get_str_list_all_threads(thread_list_t *threads)
{
    int size = get_size_list_threads(threads);
    char *str = malloc(sizeof(char) * (size + 3));
    thread_t *tmp = threads->first;

    if (!str)
        return NULL;
    memset(str, 0, size + 3);
    strcat(str, "[");
    while (tmp) {
        strcat(str, tmp->title);
        strcat(str, ": ");
        strcat(str, tmp->uuid);
        strcat(str, ", ");
        tmp = tmp->next;
    }
    strcat(str, "]");
    return str;
}

static int get_size_list_channels(channel_list_t *channels)
{
    int size = 0;
    channel_t *tmp = channels->first;

    while (tmp) {
        size += strlen(tmp->name) + 2 + strlen(tmp->uuid) + 3;
        tmp = tmp->next;
    }
    return size;
}

char *get_str_list_all_channels(channel_list_t *channels)
{
    int size = get_size_list_channels(channels);
    char *str = malloc(sizeof(char) * (size + 3));
    channel_t *tmp = channels->first;

    if (!str)
        return NULL;
    memset(str, 0, size + 3);
    strcat(str, "[");
    while (tmp) {
        strcat(str, tmp->name);
        strcat(str, ": ");
        strcat(str, tmp->uuid);
        strcat(str, ", ");
        tmp = tmp->next;
    }
    strcat(str, "]");
    return str;
}

static int get_size_list_comments(comment_list_t *comments)
{
    int size = 0;
    comment_t *tmp = comments->first;

    while (tmp) {
        size += strlen(tmp->uuid) + 2 + strlen(tmp->content) + 8 +
            strlen(tmp->author_uuid) + 3;
        tmp = tmp->next;
    }
    return size;
}

char *get_str_list_all_comments(comment_list_t *comments)
{
    int size = get_size_list_comments(comments);
    char *str = malloc(sizeof(char) * (size + 3));
    comment_t *tmp = comments->first;

    if (!str)
        return NULL;
    memset(str, 0, size + 3);
    strcat(str, "[");
    while (tmp) {
        strcat(str, tmp->uuid);
        strcat(str, ": ");
        strcat(str, tmp->content);
        strcat(str, "\nBY : ");
        strcat(str, tmp->author_uuid);
        strcat(str, ", ");
        tmp = tmp->next;
    }
    strcat(str, "]");
    return str;
}
