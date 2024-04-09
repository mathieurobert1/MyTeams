/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** string
*/

#include <unistd.h> // read
#include <stdlib.h> // malloc

char *deserialize_string(int fd)
{
    size_t len = 0;
    char *str = NULL;

    read(fd, &len, sizeof(size_t));
    str = malloc(sizeof(char) * (len + 1));
    if (!str)
        return NULL;
    read(fd, str, len);
    str[len] = '\0';
    return str;
}
