/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** list threads
*/

#include "types.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lists.h"

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
    thread->content = NULL;
    thread->title = strdup(title);
    thread->uuid = strdup(uuid);
    thread->comments = init_list_comments();
    add_to_list_threads(list_threads, thread);
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
    if (thread->content)
        free(thread->content);
    if (thread->comments)
        delete_list_comments(thread->comments);
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

void add_to_list_threads(thread_list_t *list, thread_t *thread)
{
    thread_t *tmp = list->first;

    if (list->nb_thread == 0) {
        list->first = thread;
        list->last = thread;
        thread->last = NULL;
        thread->next = NULL;
        list->nb_thread++;
        return;
    }
    list->first = thread;
    thread->last = NULL;
    tmp->last = thread;
    thread->next = tmp;
    list->nb_thread++;
}
