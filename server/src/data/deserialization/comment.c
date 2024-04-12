/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** comment
*/

#include "types.h"  // comment_t, comment_list_t
#include "data.h"   // deserialize_string
#include "lists.h"  // add_to_list_comments

#include <unistd.h> // read
#include <stdlib.h> // malloc

comment_t *deserialize_comment(int fd)
{
    comment_t *comment = malloc(sizeof(comment_t));

    if (!comment)
        return NULL;
    read(fd, comment, sizeof(comment_t));
    comment->last = NULL;
    comment->next = NULL;
    comment->uuid = deserialize_string(fd);
    comment->content = deserialize_string(fd);
    comment->author_uuid = deserialize_string(fd);
    return comment;
}

comment_list_t *deserialize_comment_list(int fd)
{
    comment_list_t *list = malloc(sizeof(comment_list_t));
    comment_t *tmp = NULL;
    int tmp_nb_comment = 0;

    if (!list)
        return NULL;
    if (read(fd, list, sizeof(comment_list_t)) == 0)
        list->nb_comment = 0;
    list->first = NULL;
    list->last = NULL;
    tmp_nb_comment = list->nb_comment;
    list->nb_comment = 0;
    for (int i = 0; i < tmp_nb_comment; i++) {
        tmp = deserialize_comment(fd);
        if (!tmp)
            return NULL;
        add_to_list_comment(list, tmp);
    }
    return list;
}
