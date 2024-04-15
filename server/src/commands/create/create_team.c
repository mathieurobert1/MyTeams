/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** create Teams
*/

#include "types.h"
#include "protocol.h"
#include "utils.h"
#include "lists.h"
#include "commands.h"
#include "logging_server.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *int_to_char(int nb)
{
    char *str = malloc(sizeof(char) * 4);

    if (!str)
        return NULL;
    memset(str, 0, 4);
    sprintf(str, "%d", nb);
    return str;
}

char *get_message_create(char *team_uuid, char *team_name,
    char *team_description, int code)
{
    size_t len = strlen(team_uuid) + strlen(team_name) +
    strlen(team_description) + 10;
    char *message = malloc(sizeof(char) * (len + 1));
    char *chcode = int_to_char(code);

    if (!message)
        return NULL;
    memset(message, 0, len + 1);
    strcat(message, chcode);
    strcat(message, " ");
    strcat(message, team_uuid);
    strcat(message, " \"");
    strcat(message, team_name);
    strcat(message, "\" \"");
    strcat(message, team_description);
    strcat(message, "\"");
    return message;
}

static void send_create_team_message(char **command, char *uuid,
    server_t *myServ, client_t *client)
{
    char *msg = get_message_create(uuid, command[1], command[2],
    CLIENT_PRINT_TEAM_CREATED);
    char *msg_all = get_message_create(uuid, command[1], command[2],
    CLIENT_EVENT_TEAM_CREATED);
    client_t *tmp = myServ->_list_client->first;

    if (!msg)
        return;
    if (!msg_all)
        return;
    if (FD_ISSET(client->_fd, &myServ->writefds))
        dprintf(client->_fd, "%s\r\n", msg);
    while (tmp) {
        if (tmp->_user_data && FD_ISSET(tmp->_fd, &myServ->writefds))
            dprintf(tmp->_fd, "%s\r\n", msg_all);
        tmp = tmp->_next;
    }
    free(msg);
    free(msg_all);
}

static bool is_team_name_exist(team_list_t *list, char *name,
    client_t *client, server_t *myServ)
{
    team_t *team = list->first;

    while (team) {
        if (strcmp(team->name, name) == 0) {
            ptc_send(CLIENT_ERROR_ALREADY_EXIST, "",
            client->_fd, &myServ->writefds);
            return true;
        }
        team = team->next;
    }
    return false;
}

void create_new_team(char **command, server_t *myServ, client_t *client)
{
    char *uuid = NULL;
    team_t *team = NULL;

    if (!is_no_error(command, myServ, client, MAX_DESCRIPTION_LENGTH))
        return;
    if (is_team_name_exist(myServ->_list_teams, command[1], client, myServ))
        return;
    uuid = create_uuid();
    if (!uuid)
        return;
    team = create_team(myServ->_list_teams, uuid, command[1], command[2]);
    add_to_list_users(team->users, client->_user_data);
    server_event_team_created(uuid, command[1], client->_user_data->uuid);
    send_create_team_message(command, uuid, myServ, client);
    free(uuid);
}
