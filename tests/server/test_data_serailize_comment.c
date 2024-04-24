/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** test_data_serailize_comment
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "data.h"

Test(serialize_comment, serialization_test) {
    char filename[] = "temp_test_file_comment";
    int fd = creat(filename, 0644);

    comment_t test_comment = {
        .uuid = "comment_uuid",
        .content = "Test comment content",
        .author_uuid = "author_uuid"
    };

    serialize_comment(fd, &test_comment);

    close(fd);

    fd = open(filename, O_RDONLY);

    comment_t read_comment;
    read(fd, &read_comment, sizeof(comment_t));
    cr_assert_str_eq(read_comment.uuid, test_comment.uuid, "Serialized comment UUID incorrect");
    cr_assert_str_eq(read_comment.content, test_comment.content, "Serialized comment content incorrect");
    cr_assert_str_eq(read_comment.author_uuid, test_comment.author_uuid, "Serialized comment author UUID incorrect");

    close(fd);

    remove(filename);
}

Test(serialize_comment_list, serialization_test) {
    char filename[] = "temp_test_file_comment_list";
    int fd = creat(filename, 0644);

    comment_t comment1 = {.uuid = "comment1_uuid", .content = "Comment1 content", .author_uuid = "author1_uuid"};
    comment_t comment2 = {.uuid = "comment2_uuid", .content = "Comment2 content", .author_uuid = "author2_uuid"};
    comment_t comment3 = {.uuid = "comment3_uuid", .content = "Comment3 content", .author_uuid = "author3_uuid"};

    comment_list_t *list = (comment_list_t *)malloc(sizeof(comment_list_t));
    list->first = &comment1;
    comment1.next = &comment2;
    comment2.next = &comment3;
    comment3.next = NULL;

    serialize_comment_list(fd, list);

    close(fd);

    fd = open(filename, O_RDONLY);

    comment_list_t read_list;
    read(fd, &read_list, sizeof(comment_list_t));
    cr_assert_not_null(read_list.first, "Serialized comment list is NULL");

    comment_t *tmp = read_list.first;
    cr_assert_str_eq(tmp->uuid, "comment1_uuid", "Serialized comment UUID of comment1 incorrect");
    cr_assert_str_eq(tmp->content, "Comment1 content", "Serialized comment content of comment1 incorrect");
    cr_assert_str_eq(tmp->author_uuid, "author1_uuid", "Serialized comment author UUID of comment1 incorrect");

    tmp = tmp->next;
    cr_assert_str_eq(tmp->uuid, "comment2_uuid", "Serialized comment UUID of comment2 incorrect");
    cr_assert_str_eq(tmp->content, "Comment2 content", "Serialized comment content of comment2 incorrect");
    cr_assert_str_eq(tmp->author_uuid, "author2_uuid", "Serialized comment author UUID of comment2 incorrect");

    tmp = tmp->next;
    cr_assert_str_eq(tmp->uuid, "comment3_uuid", "Serialized comment UUID of comment3 incorrect");
    cr_assert_str_eq(tmp->content, "Comment3 content", "Serialized comment content of comment3 incorrect");
    cr_assert_str_eq(tmp->author_uuid, "author3_uuid", "Serialized comment author UUID of comment3 incorrect");

    close(fd);

    remove(filename);
}
