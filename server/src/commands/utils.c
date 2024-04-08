/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** utils
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "protocol.h"
#include <uuid/uuid.h>

bool is_too_few_args(char **command, size_t nb_args,
    int fd_client, fd_set *writefds)
{
    size_t len_command = 0;

    for (size_t i = 0; command[i] != NULL; i++)
        len_command++;
    if (nb_args > (len_command - 1)) {
        ptc_send(TOO_FEW_PARAMETERS, "Too few arguments",
        fd_client, writefds);
        return true;
    }
    return false;
}

bool is_too_more_args(char **command, size_t nb_args,
    int fd_client, fd_set *writefds)
{
    size_t len_command = 0;

    for (size_t i = 0; command[i] != NULL; i++)
        len_command++;
    if (nb_args < (len_command - 1)) {
        ptc_send(TOO_MORE_PARAMETERS, "Too more arguments",
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

char *create_uuid(void)
{
    uuid_t binuuid;
    char *uuid = malloc(37);

    if (!uuid)
        return NULL;
    uuid_generate_random(binuuid);
    uuid_unparse_lower(binuuid, uuid);
    return uuid;
}
