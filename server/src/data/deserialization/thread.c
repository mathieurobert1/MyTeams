/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** thread
*/

#include "types.h"  // thread_t, thread_list_t
#include "lists.h"  // add_to_list_threads
#include "data.h"   // deserialize_string

#include <unistd.h> // read
#include <stdlib.h> // malloc

thread_t *deserialize_thread(int fd)
{
    thread_t *thread = malloc(sizeof(thread_t));

    if (!thread)
        return NULL;
    read(fd, thread, sizeof(thread_t));
    thread->uuid = deserialize_string(fd);
    thread->title = deserialize_string(fd);
    thread->message = deserialize_string(fd);
    thread->next = NULL;
    thread->last = NULL;
    return thread;
}

thread_list_t *deserialize_thread_list(int fd)
{
    thread_list_t *list = malloc(sizeof(thread_list_t));
    thread_t *tmp = NULL;
    int tmp_nb_thread = 0;

    if (!list)
        return NULL;
    read(fd, list, sizeof(thread_list_t));
    list->first = NULL;
    list->last = NULL;
    tmp_nb_thread = list->nb_thread;
    list->nb_thread = 0;
    for (int i = 0; i < tmp_nb_thread; i++) {
        tmp = deserialize_thread(fd);
        if (!tmp)
            return NULL;
        add_to_list_threads(list, tmp);
    }
    return list;
}
