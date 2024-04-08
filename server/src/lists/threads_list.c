/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** list threads
*/

#include "types.h"
#include <stdlib.h>
#include <unistd.h>

thread_list_t *init_list_threads(void)
{
    thread_list_t *thread_list = malloc(sizeof(thread_list_t));

    if (!thread_list)
        return NULL;
    thread_list->first = NULL;
    thread_list->last = NULL;
    thread_list->nb_thread = 0;
    return thread_list;
}

thread_t *create_thread(thread_list_t *list_threads, char *uuid, char *title)
{
    thread_t *thread = malloc(sizeof(thread_t));

    if (!thread)
        return NULL;
    thread->last = NULL;
    thread->next = NULL;
    thread->message = NULL;
    thread->title = strdup(title);
    thread->uuid = strdup(uuid);
    return thread;
}

void delete_thread(thread_t *thread)
{
    if (!thread)
        return;
    if (thread->title)
        free(thread->title);
    if (thread->uuid)
        free(thread->uuid);
    if (thread->message)
        free(thread->message);
    free(thread);
}

void delete_list_threads(thread_list_t *list_threads)
{
    thread_t *tmp = NULL;
    thread_t *tmp2 = NULL;

    if (!list_threads)
        return;
    tmp = list_threads->first;
    while (tmp) {
        tmp2 = tmp->next;
        delete_thread(tmp);
        tmp = tmp2;
    }
    free(list_threads);
}
