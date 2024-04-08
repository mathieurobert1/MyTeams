/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** utils
*/

#pragma once

#include "types.h"

#include <stdbool.h>

/**
 * @brief check if the command has too few arguments
 *
 * @param command user command
 * @param nb_args nb args required
 * @param fd_client client fd
 * @param writefds select variable to check if client can write
 * @return true
 * @return false
 */
bool is_too_few_args(char **command, size_t nb_args,
    int fd_client, fd_set *writefds);

/**
 * @brief check if the command has too more arguments
 *
 * @param command user command
 * @param nb_args nb args required
 * @param fd_client client fd
 * @param writefds select variable to check if client can write
 * @return true
 * @return false
 */
bool is_too_more_args(char **command, size_t nb_args,
    int fd_client, fd_set *writefds);

/**
 * @brief check if the command has the correct number of args
 *
 * @param command user command
 * @param nb_args nb args required
 * @param fd_client client fd
 * @param writefds select variable to check if client can write
 * @return true
 * @return false
 */
bool is_correct_command(fd_set *writefds, char **command,
    size_t nb_args, int fd_client);

/**
 * @brief create an uuid
 *
 * @return char* of the uuid
 */
char *create_uuid(void);

/**
 * @brief get the user by uuid
 *
 * @param uuid user uuid
 * @param myServ server structure
 * @return user_t* user structure
 */
user_t *getUserByUuid(char *uuid, server_t *myServ);
