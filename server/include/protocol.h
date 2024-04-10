/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** protocol
*/

#pragma once

#include <sys/select.h>

typedef enum ptc_state {
    HELP = 214,
    LOGED_OUT = 221,
    LOGED_IN = 230,
    COMMAND_SUCCESS = 200,

    UNKNOWN_USER = 400,
    SYNTAX_ERROR = 500,
    ERROR_PARAMETERS = 501,
    TOO_MORE_PARAMETERS = 502,
    TOO_FEW_PARAMETERS = 503,
    NOT_LOGED_IN = 530,

    MESSAGE_SEND = 600,
    MESSAGE_RECIEVE = 601
} ptc_state_t;

/**
 * @brief send a msg to a given file descriptor
 *
 * @param state the protocol state
 * @param msg body of the message
 * @param fd file descriptor to writte in
 * @param writefds ...
 */
void ptc_send(ptc_state_t state, char *msg, int fd, fd_set *writefds);
