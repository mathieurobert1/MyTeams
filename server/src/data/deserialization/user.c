/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** user
*/

#include "types.h"  // user_t, user_list_t
#include "lists.h"  // add_to_list_users
#include "data.h"   // deserialize_message_list, deserialize_string

#include <unistd.h> // read
#include <stdlib.h> // malloc

user_t *deserialize_user(int fd)
{
    user_t *user = malloc(sizeof(user_t));

    if (!user)
        return NULL;
    read(fd, user, sizeof(user_t));
    user->last = NULL;
    user->next = NULL;
    user->uuid = deserialize_string(fd);
    user->username = deserialize_string(fd);
    user->messages = deserialize_message_list(fd);
    return user;
}

user_list_t *deserialize_user_list(int fd)
{
    user_list_t *list = malloc(sizeof(user_list_t));
    user_t *tmp = NULL;
    int tmp_nb_user = 0;

    if (!list)
        return NULL;
    if (read(fd, list, sizeof(user_list_t)) == 0)
        list->nb_user = 0;
    list->first = NULL;
    list->last = NULL;
    tmp_nb_user = list->nb_user;
    list->nb_user = 0;
    for (int i = 0; i < tmp_nb_user; i++) {
        tmp = deserialize_user(fd);
        if (!tmp)
            return NULL;
        add_to_list_users(list, tmp);
    }
    return list;
}
