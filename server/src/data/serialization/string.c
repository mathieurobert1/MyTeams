/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** string
*/

#include <unistd.h> // write
#include <string.h> // strlen

void serialize_string(int fd, char *str)
{
    size_t len = 0;

    len = strlen(str);
    write(fd, &len, sizeof(size_t));
    write(fd, str, len);
}
