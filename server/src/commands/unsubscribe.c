/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** unsubscribe
*/

#include "types.h"
#include "utils.h"
#include "protocol.h"
#include "lists.h"
#include "logging_server.h"

#include <unistd.h>
#include <string.h>
#include <stdio.h>

static void remove_user(user_list_t *list, user_t *user)
{
    if (user->next)
        user->next->last = user->last;
    if (user->last)
        user->last->next = user->next;
    if (list->first == user)
        list->first = user->next;
    if (list->first)
        list->first->last = NULL;
    if (list->last == user)
        list->last = user->last;
    if (list->last)
        list->last->next = NULL;
    list->nb_user--;
}

static bool remove_user_from_team(team_t *team, user_t *user)
{
    user_list_t *list = team->users;
    user_t *tmp = list->first;

    while (tmp) {
        if (strcmp(tmp->uuid, user->uuid) == 0) {
            remove_user(list, tmp);
            return true;
        }
    }
    return false;
}

void unsubscribe_command(char **command, server_t *myServ, client_t *client)
{
    team_t *team = NULL;

    if (!is_correct_command(&myServ->writefds, command, 1, client->_fd))
        return;
    team = team_get_by_uuid(command[1], myServ->_list_teams);
    if (!team) {
        ptc_send(CLIENT_ERROR_UNKNOWN_TEAM, command[1],
        client->_fd, &myServ->writefds);
        return;
    }
    if (!remove_user_from_team(team, client->_user_data)) {
        ptc_send(CLIENT_ERROR_UNKNOWN_TEAM, command[1],
        client->_fd, &myServ->writefds);
        return;
    }
    server_event_user_unsubscribed(command[1], client->_user_data->uuid);
    dprintf(client->_fd, "%i \"%s\" \"%s\"\r\n", CLIENT_PRINT_UNSUBSCRIBED,
    client->_user_data->uuid, command[1]);
}
