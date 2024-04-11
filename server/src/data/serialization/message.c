/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** message
*/

#include "types.h"  // message_t, message_list_t
#include "data.h"   // serialize_string

#include <unistd.h> // write

void serialize_message(int fd, message_t *message)
{
    write(fd, message, sizeof(message_t));
    serialize_string(fd, message->sender_uuid);
    serialize_string(fd, message->receiver_uuid);
    serialize_string(fd, message->message);
}

void serialize_message_list(int fd, message_list_t *list)
{
    message_t *tmp = list->first;

    write(fd, list, sizeof(message_list_t));
    while (tmp) {
        serialize_message(fd, tmp);
        tmp = tmp->next;
    }
}
