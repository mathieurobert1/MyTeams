/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** subscribed
*/

#include "types.h"      // team_t, user_t, team_list_t, user_list_t
#include "utils.h"      // is_too_more_args
#include "protocol.h"   // ptc_send

#include <stddef.h> // NULL
#include <string.h> // memset, strcat
#include <stdlib.h> // malloc

static bool is_user_subscribed_to_team(team_t *team, user_t *user)
{
    user_list_t *list_users = team->users;
    user_t *tmp = list_users->first;

    while (tmp) {
        if (tmp == user)
            return true;
        tmp = tmp->next;
    }
    return false;
}

static size_t get_size_list_teams(team_list_t *list_teams, user_t *user)
{
    size_t size = 0;
    team_t *tmp = list_teams->first;

    while (tmp) {
        if (is_user_subscribed_to_team(tmp, user)) {
            size += strlen(tmp->name);
            size += strlen(tmp->uuid);
            size += 3 + 2;
        }
        tmp = tmp->next;
    }
    return size;
}

char *get_message_list_team(team_list_t *list_teams, user_t *user)
{
    size_t size = get_size_list_teams(list_teams, user);
    char *msg = malloc(sizeof(char) * (size + 1));
    team_t *tmp = list_teams->first;

    if (!msg)
        return NULL;
    memset(msg, 0, size + 1);
    strcat(msg, "[");
    while (tmp) {
        if (is_user_subscribed_to_team(tmp, user)) {
            strcat(msg, tmp->name);
            strcat(msg, " : ");
            strcat(msg, tmp->uuid);
            strcat(msg, ", ");
        }
        tmp = tmp->next;
    }
    strcat(msg, "]");
    return msg;
}

static size_t get_size_list_users(user_list_t *list_users)
{
    size_t size = 0;
    user_t *tmp = list_users->first;

    while (tmp) {
        size += strlen(tmp->username);
        size += strlen(tmp->uuid);
        size += 3 + 2;
        tmp = tmp->next;
    }
    return size;
}

char *get_message_list_users(user_list_t *list_users)
{
    size_t size = get_size_list_users(list_users);
    char *msg = malloc(sizeof(char) * (size + 1));
    user_t *tmp = list_users->first;

    if (!msg)
        return NULL;
    memset(msg, 0, size + 1);
    strcat(msg, "[");
    while (tmp) {
        strcat(msg, tmp->username);
        strcat(msg, " : ");
        strcat(msg, tmp->uuid);
        strcat(msg, ", ");
        tmp = tmp->next;
    }
    strcat(msg, "]");
    return msg;
}
