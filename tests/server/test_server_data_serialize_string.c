/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** test_server_data_serialize_string
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "server/include/data.h"

Test(serialize_string, serialization_test) {
    char filename[] = "temp_test_file";
    int fd = creat(filename, 0644);

    char *test_string = "Hello, world!";

    serialize_string(fd, test_string);

    close(fd);

    fd = open(filename, O_RDONLY);

    size_t len;
    read(fd, &len, sizeof(size_t));
    cr_assert_eq(len, strlen(test_string), "Serialized string length incorrect");

    char read_string[len + 1];
    read(fd, read_string, len);
    read_string[len] = '\0';
    cr_assert_str_eq(read_string, test_string, "Serialized string incorrect");

    close(fd);

    remove(filename);
}

Test(serialize_string, empty_string_test) {
    char filename[] = "temp_test_file_empty";
    int fd = creat(filename, 0644);

    char *empty_string = "";

    serialize_string(fd, empty_string);

    close(fd);

    fd = open(filename, O_RDONLY);

    size_t len;
    read(fd, &len, sizeof(size_t));
    cr_assert_eq(len, 0, "Serialized empty string length incorrect");

    close(fd);

    remove(filename);
}
