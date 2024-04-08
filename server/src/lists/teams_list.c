/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** list teams
*/

#include "types.h"
#include <stdlib.h>
#include <unistd.h>

team_list_t *init_list_teams(void)
{
    team_list_t *team_list = malloc(sizeof(team_list_t));

    if (!team_list)
        return NULL;
    team_list->first = NULL;
    team_list->last = NULL;
    team_list->nb_team = 0;
    return team_list;
}

team_t *create_team(team_list_t *list_teams, char *uuid, char *name)
{
    team_t *team = malloc(sizeof(team_t));

    if (!team)
        return NULL;
    team->last = NULL;
    team->next = NULL;
    team->channels = NULL;
    team->description = NULL;
    team->name = strdup(name);
    team->users = NULL;
    team->uuid = strdup(uuid);
    return team;
}

void delete_team(team_t *user)
{
    if (!user)
        return;
    if (user->name)
        free(user->name);
    if (user->uuid)
        free(user->uuid);
    if (user->description)
        free(user->description);
    if (user->description)
        free(user->description);    
    free(user);
}

void delete_list_teams(team_list_t *list_teams)
{
    team_t *tmp = NULL;
    team_t *tmp2 = NULL;

    if (!list_teams)
        return;
    tmp = list_teams->first;
    while (tmp) {
        tmp2 = tmp->next;
        delete_team(tmp);
        tmp = tmp2;
    }
    free(list_teams);
}

void add_to_list_team(team_list_t *list, team_t *team)
{
    client_t *tmp = list->first;

    if (list->nb_team == 0) {
        list->first = team;
        list->last = team;
        team->last = NULL;
        team->next = NULL;
        list->nb_team++;
        return;
    }
    list->first = team;
    team->last = NULL;
    tmp->_last = team;
    team->next = tmp;
    list->nb_team++;
}
