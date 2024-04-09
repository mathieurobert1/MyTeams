/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** user
*/

#include "types.h"  // user_t, user_list_t
#include "data.h"   // serialize_message_list, serialize_string

#include <unistd.h> // write

void serialize_user(int fd, user_t *user)
{
    write(fd, user, sizeof(user_t));
    serialize_string(fd, user->uuid);
    serialize_string(fd, user->username);
    serialize_message_list(fd, user->messages);
}

void serialize_user_list(int fd, user_list_t *list)
{
    user_t *tmp = list->first;

    write(fd, list, sizeof(user_list_t));
    while (tmp) {
        serialize_user(fd, tmp);
        tmp = tmp->next;
    }
}
