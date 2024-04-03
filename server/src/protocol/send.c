/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** send
*/

#include "protocol.h"

#include <stdio.h>

void ptc_send(ptc_state_t state, char *msg, int fd, fd_set *writefds)
{
    if (FD_ISSET(fd, writefds)) {
        dprintf(fd, "%i %s\n", state, msg);
    }
}
