/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** get_uuid
*/

#include "types.h"

#include <unistd.h>
#include <string.h>

user_t *get_user_by_uuid(char *uuid, server_t *myServ)
{
    user_list_t *list = myServ->_list_users;
    user_t *user = list->first;

    for (size_t i = 0; user != NULL; i++) {
        if (strcmp(user->uuid, uuid) == 0)
            return user;
        user = user->next;
    }
    return NULL;
}

team_t *get_team_by_uuid(char *uuid, server_t *myServ)
{
    team_list_t *list = myServ->_list_teams;
    team_t *team = list->first;

    for (size_t i = 0; team != NULL; i++) {
        if (strcmp(team->uuid, uuid) == 0)
            return team;
        team = team->next;
    }
    return NULL;
}
