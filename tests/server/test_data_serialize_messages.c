/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** test_data_serialize_messages
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "server/include/types.h"
#include "server/include/data.h"

Test(serialize_message, serialization_test) {
    char filename[] = "temp_test_file_message";
    int fd = creat(filename, 0644);

    message_t test_message = {
        .sender_uuid = "sender_uuid",
        .receiver_uuid = "receiver_uuid",
        .message = "Test message"
    };

    serialize_message(fd, &test_message);
    close(fd);

    fd = open(filename, O_RDONLY);

    message_t read_message;
    read(fd, &read_message, sizeof(message_t));
    cr_assert_str_eq(read_message.sender_uuid, test_message.sender_uuid, "Serialized sender UUID incorrect");
    cr_assert_str_eq(read_message.receiver_uuid, test_message.receiver_uuid, "Serialized receiver UUID incorrect");
    cr_assert_str_eq(read_message.message, test_message.message, "Serialized message incorrect");

    close(fd);

    remove(filename);
}

Test(serialize_message_list, serialization_test) {
    char filename[] = "temp_test_file_message_list";
    int fd = creat(filename, 0644);

    message_t message1 = {.sender_uuid = "sender1", .receiver_uuid = "receiver1", .message = "Message1"};
    message_t message2 = {.sender_uuid = "sender2", .receiver_uuid = "receiver2", .message = "Message2"};
    message_t message3 = {.sender_uuid = "sender3", .receiver_uuid = "receiver3", .message = "Message3"};

    (void)fd;
    (void)filename;
    message_list_t *list = (message_list_t *)malloc(sizeof(message_list_t));
    list->first = &message1;
    message1.next = &message2;
    message2.next = &message3;
    message3.next = NULL;

    serialize_message_list(fd, list);

    close(fd);

    fd = open(filename, O_RDONLY);

    message_list_t read_list;
    read(fd, &read_list, sizeof(message_list_t));
    cr_assert_not_null(read_list.first, "Serialized message list is NULL");

    message_t *tmp = read_list.first;
    cr_assert_str_eq(tmp->sender_uuid, "sender1", "Serialized sender UUID of message1 incorrect");
    cr_assert_str_eq(tmp->receiver_uuid, "receiver1", "Serialized receiver UUID of message1 incorrect");
    cr_assert_str_eq(tmp->message, "Message1", "Serialized message1 incorrect");

    tmp = tmp->next;
    cr_assert_str_eq(tmp->sender_uuid, "sender2", "Serialized sender UUID of message2 incorrect");
    cr_assert_str_eq(tmp->receiver_uuid, "receiver2", "Serialized receiver UUID of message2 incorrect");
    cr_assert_str_eq(tmp->message, "Message2", "Serialized message2 incorrect");

    tmp = tmp->next;
    cr_assert_str_eq(tmp->sender_uuid, "sender3", "Serialized sender UUID of message3 incorrect");
    cr_assert_str_eq(tmp->receiver_uuid, "receiver3", "Serialized receiver UUID of message3 incorrect");
    cr_assert_str_eq(tmp->message, "Message3", "Serialized message3 incorrect");

    close(fd);

    remove(filename);
}
