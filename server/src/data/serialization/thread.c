/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** thread
*/

#include "types.h"  // thread_t, thread_list_t
#include "data.h"   // serialize_string

#include <unistd.h> // write

void serialize_thread(int fd, thread_t *thread)
{
    write(fd, thread, sizeof(thread_t));
    serialize_string(fd, thread->uuid);
    serialize_string(fd, thread->title);
    serialize_string(fd, thread->content);
    serialize_comment_list(fd, thread->comments);
}

void serialize_thread_list(int fd, thread_list_t *list)
{
    thread_t *tmp = list->first;

    write(fd, list, sizeof(thread_list_t));
    while (tmp) {
        serialize_thread(fd, tmp);
        tmp = tmp->next;
    }
}
