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
#include <stdio.h> // dprintf

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

static void print_list_team(server_t *server, client_t *client)
{
    team_t *tmp = server->_list_teams->first;
    int fd = client->_fd;
    fd_set *writefds = &server->writefds;

    if (FD_ISSET(fd, writefds) && !tmp)
        dprintf(fd, "%d \"%s\"", CLIENT_ERROR_UNKNOWN_TEAM,
            client->_use_uuid_team);
    while (tmp) {
        if (is_user_subscribed_to_team(tmp, client->_user_data) &&
            FD_ISSET(fd, writefds)) {
                dprintf(fd, "%d \"%s\" \"%s\" \"%s\"\n", CLIENT_PRINT_TEAM,
                    tmp->uuid, tmp->name, tmp->description);
        }
        tmp = tmp->next;
    }
    if (FD_ISSET(fd, writefds))
        dprintf(fd, "\n\r");
}

static void print_list_users(user_list_t *list_users, int fd, fd_set *writefds)
{
    user_t *tmp = list_users->first;

    while (tmp) {
        if (FD_ISSET(fd, writefds))
            dprintf(fd, "%d \"%s\" \"%s\" \"%d\"\n", CLIENT_PRINT_USERS,
                tmp->uuid, tmp->username, tmp->is_logged);
        tmp = tmp->next;
    }
    if (FD_ISSET(fd, writefds))
        dprintf(fd, "\n\r");
}

static void print_message_team(server_t *myServ, char *team_uuid, int fd,
    fd_set *writefds)
{
    team_list_t *list_teams = myServ->_list_teams;
    team_t *tmp = list_teams->first;

    while (tmp) {
        if (strcmp(tmp->uuid, team_uuid) == 0) {
            print_list_users(tmp->users, fd, writefds);
        }
        tmp = tmp->next;
    }
}

void subscribed_command(char **command, server_t *myServ, client_t *client)
{
    if (is_too_more_args(command, 1, client->_fd, &myServ->writefds))
        return;
    if (command[1] == NULL)
        print_list_team(myServ, client);
    else {
        print_message_team(myServ, command[1], client->_fd, &myServ->writefds);
    }
}
