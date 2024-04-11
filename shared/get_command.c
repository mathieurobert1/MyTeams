/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** get_command
*/
#include "shared.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void delete_list_arg(char **list_arg)
{
    for (int i = 0; list_arg[i] != NULL; i++)
        free(list_arg[i]);
    if (list_arg)
        free(list_arg);
}

static char *get_between_quote(char *buffer, int *len, int len_buffer)
{
    int nb_char = 0;
    char *message = NULL;

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '\"')
            break;
        if (*len + nb_char == len_buffer - 1)
            return NULL;
        nb_char += 1;
    }
    message = malloc(sizeof(char) * (nb_char + 1));
    if (!message)
        return NULL;
    for (int i = 0; i < nb_char; i++)
        message[i] = buffer[i];
    message[nb_char] = '\0';
    *len += nb_char + 2;
    return message;
}

static char *get_between_spaces(char *buffer, int *len, int len_buffer)
{
    int nb_char = 0;
    char *message = NULL;

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == ' ' || buffer[i] == '\"' ||
            *len + nb_char == len_buffer)
            break;
        nb_char += 1;
    }
    message = malloc(sizeof(char) * (nb_char + 1));
    if (!message)
        return NULL;
    for (int i = 0; i < nb_char; i++)
        message[i] = buffer[i];
    message[nb_char] = '\0';
    *len += nb_char;
    return message;
}

static char **my_realloc(char **list_arg, char *arg, int len_processed)
{
    char **tmp = realloc(list_arg, sizeof(char *) * (len_processed + 1));

    if (!tmp)
        return NULL;
    if (!arg)
        return NULL;
    tmp[len_processed - 1] = arg;
    tmp[len_processed] = NULL;
    return tmp;
}

static char **get_args(char *buffer,
    int *idx, char **list_arg, int *len_processed)
{
    char *arg = NULL;
    int len_buffer = strlen(buffer) - 2;

    if (buffer[*idx] == '\"') {
        arg = get_between_quote(buffer + *idx + 1, idx, len_buffer);
        *len_processed += 1;
    } else if (buffer[*idx] != ' ') {
        arg = get_between_spaces(buffer + *idx, idx, len_buffer);
        *len_processed += 1;
    } else {
        *idx += 1;
        return list_arg;
    }
    list_arg = my_realloc(list_arg, arg, *len_processed);
    if (!list_arg)
        return NULL;
    return list_arg;
}

char **get_list_arg(char *buffer)
{
    char **list_arg = NULL;
    int len_buffer = strlen(buffer) - 2;
    int idx = 0;
    int len_processed = 0;

    if (len_buffer <= 0)
        return NULL;
    list_arg = malloc(sizeof(char *) * 1);
    if (!list_arg)
        return NULL;
    list_arg[0] = NULL;
    while (idx < len_buffer) {
        list_arg = get_args(buffer, &idx, list_arg, &len_processed);
        if (!list_arg)
            return NULL;
    }
    if (len_processed == 0)
        return NULL;
    return list_arg;
}
