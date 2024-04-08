/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** utils
*/

#include <unistd.h>
#include <stdbool.h>
#include "protocol.h"

bool is_too_few_args(char **command, size_t nb_args,
    int fd_client, fd_set *writefds)
{
    int len_command = 0;

    for (size_t i = 0; command[i] != NULL; i++)
        len_command++;
    if (nb_args < (len_command - 1)) {
        ptc_send(TOO_FEW_PARAMETERS, "Too few arguments",
        fd_client, writefds);
        return true;
    }
    return false;
}

bool is_too_more_args(char **command, size_t nb_args,
    int fd_client, fd_set *writefds)
{
    int len_command = 0;

    for (size_t i = 0; command[i] != NULL; i++)
        len_command++;
    if (nb_args > (len_command - 1)) {
        ptc_send(TOO_MORE_PARAMETERS, "Too few arguments",
        fd_client, writefds);
        return true;
    }
    return false;
}

bool is_correct_command(fd_set *writefds, char **command,
    size_t nb_args, int fd_client)
{
    if (is_too_few_args(command, nb_args, fd_client, writefds))
        return false;
    if (is_too_more_args(command, nb_args, fd_client, writefds))
        return false;
    return true;
}
