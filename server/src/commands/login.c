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

void cut_user_name_to_long(char **command)
{
    char *new_name = NULL;

    if (strlen(command[1] < MAX_NAME_LENGTH))
        return;
    new_name = malloc(sizeof(char) * (MAX_NAME_LENGTH + 1));
    for (size_t i = 0; i < MAX_NAME_LENGTH; i++)
        new_name[i] = command[1][i];
    new_name[MAX_NAME_LENGTH] = '\0';
    free(command[1]);
    command[1] = new_name;
}

void login_command(char **command, server_t *myServ, client_t *client)
{
    if (is_correct_command(&myServ->writefds,
    command, 1, client->_fd))
        return;
    if (client->_user_data) {
        ptc_send(LOGED_IN, "User logged in, proceed.",
        client->_fd, &myServ->writefds);
        return;
    }
    cut_user_name_to_long(command);
}
