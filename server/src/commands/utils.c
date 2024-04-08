/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** utils
*/

#include <unistd.h>
#include <stdbool.h>

bool is_too_few_args(char **command, size_t nb_args)
{
    int len_command = 0;

    for (size_t i = 0; command[i] != NULL; i++)
        len_command++;
    if (nb_args < (len_command - 1))
        return true;
    return false;
}

bool is_too_more_args(char **command, size_t nb_args)
{
    int len_command = 0;

    for (size_t i = 0; command[i] != NULL; i++)
        len_command++;
    if (nb_args > (len_command - 1))
        return true;
    return false;
}
