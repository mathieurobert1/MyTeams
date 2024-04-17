/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** read_command
*/

#include "types.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char *read_data_client(client_t *tmp)
{
    char buffer[1];
    char *cmd = malloc(sizeof(char) * 1024);
    int n = 0;
    int result_read = 0;

    if (!cmd)
        return NULL;
    result_read = read(tmp->_fd, buffer, 1);
    while (result_read > 0) {
        cmd[n] = buffer[0];
        if ((cmd[n] == '\n' && n != 0 && cmd[n -1] == '\r') ||
            (cmd[n] == 'n' && n != 0 && cmd[n -1] == '\\'))
            break;
        n++;
        result_read = read(tmp->_fd, buffer, 1);
    }
    cmd[n + 1] = '\0';
    if (n == 0 && result_read == 0)
        cmd = strdup("/logout\r\n");
    return cmd;
}
