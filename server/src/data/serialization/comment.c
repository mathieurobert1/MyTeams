/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** comment
*/

#include "types.h"  // comment_t, comment_list_t
#include "data.h"   // serialize_string

#include <unistd.h> // write

void serialize_comment(int fd, comment_t *comment)
{
    write(fd, comment, sizeof(comment_t));
    serialize_string(fd, comment->uuid);
    serialize_string(fd, comment->content);
    serialize_string(fd, comment->author_uuid);
}

void serialize_comment_list(int fd, comment_list_t *list)
{
    comment_t *tmp = list->first;

    write(fd, list, sizeof(comment_list_t));
    while (tmp) {
        serialize_comment(fd, tmp);
        tmp = tmp->next;
    }
}
