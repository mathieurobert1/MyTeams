/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** message
*/

#include "types.h"  // message_t, message_list_t
#include "lists.h"  // add_message_to_list
#include "data.h"   // deserialize_string

#include <unistd.h> // read
#include <stdlib.h> // malloc

message_t *deserialize_message(int fd)
{
    message_t *message = malloc(sizeof(message_t));

    if (!message)
        return NULL;
    read(fd, message, sizeof(message_t));
    message->sender_uuid = deserialize_string(fd);
    message->receiver_uuid = deserialize_string(fd);
    message->message = deserialize_string(fd);
    message->next = NULL;
    message->last = NULL;
    return message;
}

message_list_t *deserialize_message_list(int fd)
{
    message_list_t *list = malloc(sizeof(message_list_t));
    message_t *tmp = NULL;
    int tmp_nb_messages = 0;

    if (!list)
        return NULL;
    if (read(fd, list, sizeof(message_list_t)) == 0)
        list->nb_messages = 0;
    list->first = NULL;
    list->last = NULL;
    tmp_nb_messages = list->nb_messages;
    list->nb_messages = 0;
    for (int i = 0; i < tmp_nb_messages; i++) {
        tmp = deserialize_message(fd);
        if (!tmp)
            return NULL;
        add_to_list_messages(list, tmp);
    }
    return list;
}
