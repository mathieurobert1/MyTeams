/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** team
*/

#include "types.h"  // team_t, team_list_t
#include "lists.h"  // add_team_to_list
#include "data.h"   // deserialize_channel_list, deserialize_user_list,
    // deserialize_string

#include <unistd.h> // read
#include <stdlib.h> // malloc

team_t *deserialize_team(int fd)
{
    team_t *team = malloc(sizeof(team_t));

    if (!team)
        return NULL;
    read(fd, team, sizeof(team_t));
    team->uuid = deserialize_string(fd);
    team->name = deserialize_string(fd);
    team->description = deserialize_string(fd);
    team->channels = deserialize_channel_list(fd);
    team->users = deserialize_user_list(fd);
    team->next = NULL;
    team->last = NULL;
    return team;
}

team_list_t *deserialize_team_list(int fd)
{
    team_list_t *list = malloc(sizeof(team_list_t));
    team_t *tmp = NULL;
    int tmp_nb_team = 0;

    if (!list)
        return NULL;
    read(fd, list, sizeof(team_list_t));
    list->first = NULL;
    list->last = NULL;
    tmp_nb_team = list->nb_team;
    list->nb_team = 0;
    for (int i = 0; i < tmp_nb_team; i++) {
        tmp = deserialize_team(fd);
        if (!tmp)
            return NULL;
        add_to_list_team(list, tmp);
    }
    return list;
}
