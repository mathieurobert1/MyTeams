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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_message_create(char *team_uuid, char *team_name,
    char *team_description, char *code)
{
    size_t len = strlen(team_uuid) + strlen(team_name) +
    strlen(team_description) + 10;
    char *message = malloc(sizeof(char) * (len + 1));

    if (!message)
        return NULL;
    memset(message, 0, len + 1);
    strcat(message, code);
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
    char *msg = get_message_create(uuid, command[1], command[2], "930");
    char *msg_all = get_message_create(uuid, command[1], command[2], "740");
    client_t *tmp = myServ->_list_client->first;

    if (!msg)
        return;
    if (!msg_all) {
        free(msg);
        return;
    }
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

void create_new_team(char **command, server_t *myServ, client_t *client)
{
    char *uuid = NULL;

    if (!is_correct_command(&myServ->writefds, command, 2, client->_fd))
        return;
    if (strlen(command[1]) > MAX_NAME_LENGTH) {
        ptc_send(ERROR_PARAMETERS, "Too long name.",
        client->_fd, &myServ->writefds);
        return;
    }
    if (strlen(command[2]) > MAX_DESCRIPTION_LENGTH) {
        ptc_send(ERROR_PARAMETERS, "Too long description.",
        client->_fd, &myServ->writefds);
        return;
    }
    uuid = create_uuid();
    if (!uuid)
        return;
    create_team(myServ->_list_teams, uuid, command[1], command[2]);
    send_create_team_message(command, uuid, myServ, client);
    free(uuid);
}
