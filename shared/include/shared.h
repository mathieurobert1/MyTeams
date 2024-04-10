/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** shared
*/

#pragma once

/**
 * @brief Get the list of the client command
 *
 * @param buffer command in char*
 * @return char** list of char* command
 */
char **get_list_arg(char *buffer);

/**
 * @brief delete the command list
 *
 * @param list_arg command list
 */
void delete_list_arg(char **list_arg);
