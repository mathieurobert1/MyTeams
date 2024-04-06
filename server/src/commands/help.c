/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** help
*/

#include "types.h"
#include "protocol.h"

#include <stdlib.h>
#include <string.h>

static char *fill_command_help(char *buffer)
{
    size_t index = 0;

    for (size_t i = 0; _list_command[i]._name != NULL; i++) {
        for (size_t j = 0; j < strlen(_list_command[i]._name); j++) {
            buffer[index] = _list_command[i]._name[j];
            index++;
        }
        buffer[index] = ' ';
        index++;
    }
    buffer[index] = '\0';
    return buffer;
}

void help_command(char **command, server_t *myServ, client_t *client)
{
    int len_help = 0;
    char *help_msg = NULL;

    if (command[1]) {
        ptc_send(TO_MORE_PARAMETERS, "To more parameters.",
        client->_fd, &myServ->writefds);
        return;
    }
    for (int i = 0; _list_command[i]._name != NULL; i++) {
        len_help += strlen(_list_command[i]._name);
        len_help += 1;
    }
    help_msg = malloc(sizeof(char) * (len_help + 1));
    if (!help_msg)
        return;
    help_msg = fill_command_help(help_msg);
    ptc_send(HELP, help_msg, client->_fd, &myServ->writefds);
    free(help_msg);
}
