/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** login
*/

#include "types.h"
#include "protocol.h"
#include "commands.h"
#include <stdlib.h>
#include <string.h>

static void cut_user_name_to_long(char **command)
{
    char *new_name = NULL;

    if (strlen(command[1]) < MAX_NAME_LENGTH)
        return;
    new_name = malloc(sizeof(char) * (MAX_NAME_LENGTH + 1));
    for (size_t i = 0; i < MAX_NAME_LENGTH; i++)
        new_name[i] = command[1][i];
    new_name[MAX_NAME_LENGTH] = '\0';
    free(command[1]);
    command[1] = new_name;
}

static user_t *get_user_data(server_t *myServ, char *user_name)
{
    user_t *tmp = myServ->_list_users->first;
    while (tmp) {
        if (strcmp(tmp->username, user_name) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

static user_t *create_user_data(server_t *myServ, char *user_name)
{
    (void) myServ;
    user_t *new_user = malloc(sizeof(user_t));

    if (!new_user)
        return NULL;
    new_user->username = strdup(user_name);
    new_user->uuid = "/!\\ CREATE AN UUID";
    new_user->last = NULL;
    new_user->next = NULL;
    //add new_user to the user list
    return new_user;
}

void login_command(char **command, server_t *myServ, client_t *client)
{
    if (!is_correct_command(&myServ->writefds, command, 1, client->_fd))
        return;
    if (client->_user_data) {
        ptc_send(LOGED_IN, "User logged in, proceed.",
        client->_fd, &myServ->writefds);
        return;
    }
    cut_user_name_to_long(command);
    client->_user_data = get_user_data(myServ, command[1]);
    if (client->_user_data != NULL)
        return;
    client->_user_data = create_user_data(myServ, command[1]);

}
