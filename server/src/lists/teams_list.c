/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** list teams
*/

#include "types.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lists.h"

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

team_t *create_team(team_list_t *list_teams, char *uuid,
    char *name, char *description)
{
    team_t *team = malloc(sizeof(team_t));

    if (!team)
        return NULL;
    team->last = NULL;
    team->next = NULL;
    team->channels = init_list_channels();
    team->description = strdup(description);
    team->name = strdup(name);
    team->users = init_list_users();
    team->uuid = strdup(uuid);
    add_to_list_team(list_teams, team);
    return team;
}

void delete_team(team_t *team)
{
    if (!team)
        return;
    if (team->name)
        free(team->name);
    if (team->uuid)
        free(team->uuid);
    if (team->description)
        free(team->description);
    if (team->description)
        free(team->description);
    free(team);
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
    team_t *tmp = list->first;

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
    tmp->last = team;
    team->next = tmp;
    list->nb_team++;
}
