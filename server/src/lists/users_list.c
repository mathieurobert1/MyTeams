/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** list users
*/

#include "types.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lists.h"

user_list_t *init_list_users(void)
{
    user_list_t *user_list = malloc(sizeof(user_list_t));

    if (!user_list)
        return NULL;
    user_list->first = NULL;
    user_list->last = NULL;
    user_list->nb_user = 0;
    return user_list;
}

user_t *create_user(user_list_t *list_users, char *uuid, char *user_name)
{
    user_t *user = malloc(sizeof(user_t));

    if (!user)
        return NULL;
    user->last = NULL;
    user->next = NULL;
    user->username = strdup(user_name);
    user->uuid = strdup(uuid);
    add_to_list_users(list_users, user);
    return user;
}

void delete_user(user_t *user)
{
    if (!user)
        return;
    if (user->username)
        free(user->username);
    if (user->uuid)
        free(user->uuid);
    free(user);
}

void delete_list_users(user_list_t *list_users)
{
    user_t *tmp = NULL;
    user_t *tmp2 = NULL;

    if (!list_users)
        return;
    tmp = list_users->first;
    while (tmp) {
        tmp2 = tmp->next;
        delete_user(tmp);
        tmp = tmp2;
    }
    free(list_users);
}

void add_to_list_users(user_list_t *list, user_t *user)
{
    user_t *tmp = list->first;

    if (list->nb_user == 0) {
        list->first = user;
        list->last = user;
        user->last = NULL;
        user->next = NULL;
        list->nb_user++;
        return;
    }
    list->first = user;
    user->last = NULL;
    tmp->last = user;
    user->next = tmp;
    list->nb_user++;
}
