/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** read_command
*/

#include "types.h"
#include <stdlib.h>
#include <unistd.h>

char *read_data_client(client_t *tmp)
{
    char buffer[1];
    char *cmd = malloc(sizeof(char) * 1024);
    int n = 0;

    if (!cmd)
        return NULL;
    while (read(tmp->_fd, buffer, 1) > 0) {
        cmd[n] = buffer[0];
        if ((cmd[n] == '\n' && n != 0 && cmd[n -1] == '\r') ||
            (cmd[n] == 'n' && n != 0 && cmd[n -1] == '\\'))
            break;
        n++;
    }
    cmd[n + 1] = '\0';
    return cmd;
}
