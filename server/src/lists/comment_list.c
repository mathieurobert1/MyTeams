/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** list comments
*/

#include "types.h"
#include "lists.h"
#include "utils.h"

#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

comment_list_t *init_list_comments(void)
{
    comment_list_t *comment_list = malloc(sizeof(comment_list_t));

    if (!comment_list)
        return NULL;
    comment_list->first = NULL;
    comment_list->last = NULL;
    comment_list->nb_comment = 0;
    return comment_list;
}

comment_t *create_comment(comment_list_t *list_comments,
    char *content, char *author_uuid)
{
    comment_t *comment = malloc(sizeof(comment_t));
    time_t timestamp = time(NULL);
    char *uuid = create_uuid();

    if (!comment)
        return NULL;
    comment->last = NULL;
    comment->next = NULL;
    comment->content = strdup(content);
    comment->uuid = uuid;
    comment->author_uuid = strdup(author_uuid);
    comment->timestamp = timestamp;
    add_to_list_comment(list_comments, comment);
    return comment;
}

void delete_comment(comment_t *comment)
{
    if (!comment)
        return;
    if (comment->content)
        free(comment->content);
    if (comment->uuid)
        free(comment->uuid);
    if (comment->author_uuid)
        free(comment->author_uuid);
    free(comment);
}

void delete_list_comments(comment_list_t *list_comments)
{
    comment_t *tmp = NULL;
    comment_t *tmp2 = NULL;

    if (!list_comments)
        return;
    tmp = list_comments->first;
    while (tmp) {
        tmp2 = tmp->next;
        delete_comment(tmp);
        tmp = tmp2;
    }
    free(list_comments);
}

void add_to_list_comment(comment_list_t *list, comment_t *comment)
{
    comment_t *tmp = list->first;

    if (list->nb_comment == 0) {
        list->first = comment;
        list->last = comment;
        comment->last = NULL;
        comment->next = NULL;
        list->nb_comment++;
        return;
    }
    list->first = comment;
    comment->last = NULL;
    tmp->last = comment;
    comment->next = tmp;
    list->nb_comment++;
}
