/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** list messagess
*/

#include "types.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lists.h"

message_list_t *init_list_messages(void)
{
    message_list_t *messages_list = malloc(sizeof(message_list_t));

    if (!messages_list)
        return NULL;
    messages_list->first = NULL;
    messages_list->last = NULL;
    messages_list->nb_messages = 0;
    return messages_list;
}

message_t *create_messages(message_list_t *list_messagess, char *uuidReceiver, char *uuidSender, char *message)
{
    message_t *messages = malloc(sizeof(message_t));

    if (!messages)
        return NULL;
    messages->last = NULL;
    messages->next = NULL;
    messages->sender_uuid = strdup(uuidSender);
    messages->receiver_uuid = strdup(uuidReceiver);
    messages->message = strdup(message);
    add_to_list_messages(list_messagess, messages);
    return messages;
}

void delete_messages(message_t *messages)
{
    if (!messages)
        return;
    if (messages->receiver_uuid)
        free(messages->receiver_uuid);
    if (messages->sender_uuid)
        free(messages->sender_uuid);
    if (messages->message)
        free(messages->message);
    free(messages);
}

void delete_list_messages(message_list_t *list_messagess)
{
    message_t *tmp = NULL;
    message_t *tmp2 = NULL;

    if (!list_messagess)
        return;
    tmp = list_messagess->first;
    while (tmp) {
        tmp2 = tmp->next;
        delete_messages(tmp);
        tmp = tmp2;
    }
    free(list_messagess);
}

void add_to_list_messages(message_list_t *list, message_t *messages)
{
    message_t *tmp = list->first;

    if (list->nb_messages == 0) {
        list->first = messages;
        list->last = messages;
        messages->last = NULL;
        messages->next = NULL;
        list->nb_messages++;
        return;
    }
    list->first = messages;
    messages->last = NULL;
    tmp->last = messages;
    messages->next = tmp;
    list->nb_messages++;
}
