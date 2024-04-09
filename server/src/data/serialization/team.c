/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** team
*/

#include "types.h"  // team_t, team_list_t
#include "data.h"   // serialize_channel_list, serialize_user_list,
    // serialize_string

#include <unistd.h> // write

void serialize_team(int fd, team_t *team)
{
    write(fd, team, sizeof(team_t));
    serialize_string(fd, team->uuid);
    serialize_string(fd, team->name);
    serialize_string(fd, team->description);
    serialize_channel_list(fd, team->channels);
    serialize_user_list(fd, team->users);
}

void serialize_team_list(int fd, team_list_t *list)
{
    team_t *tmp = list->first;

    write(fd, list, sizeof(team_list_t));
    while (tmp) {
        serialize_team(fd, tmp);
        tmp = tmp->next;
    }
}
