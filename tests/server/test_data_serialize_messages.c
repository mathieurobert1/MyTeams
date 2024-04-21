/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** test_data_serialize_messages
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <fcntl.h>

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

    revoke(filename);
}
