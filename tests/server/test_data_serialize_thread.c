/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** test_data_serialize_thread
*/

#include <criterion/criterion.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "data.h"

Test(serialize_thread, serialization_test) {
    char filename[] = "temp_test_file_thread";
    int fd = creat(filename, 0644);

    comment_t comment1 = {.uuid = "comment1_uuid", .content = "Comment1 content", .author_uuid = "author1_uuid"};
    comment_t comment2 = {.uuid = "comment2_uuid", .content = "Comment2 content", .author_uuid = "author2_uuid"};
    comment_t comment3 = {.uuid = "comment3_uuid", .content = "Comment3 content", .author_uuid = "author3_uuid"};

    comment_list_t comments = {.first = &comment1};
    comment1.next = &comment2;
    comment2.next = &comment3;
    comment3.next = NULL;

    thread_t test_thread = {
        .uuid = "thread_uuid",
        .title = "Test thread title",
        .content = "Test thread content",
        .comments = &comments
    };

    serialize_thread(fd, &test_thread);

    close(fd);

    fd = open(filename, O_RDONLY);

    thread_t read_thread;
    read(fd, &read_thread, sizeof(thread_t));
    cr_assert_str_eq(read_thread.uuid, test_thread.uuid, "Serialized thread UUID incorrect");
    cr_assert_str_eq(read_thread.title, test_thread.title, "Serialized thread title incorrect");
    cr_assert_str_eq(read_thread.content, test_thread.content, "Serialized thread content incorrect");

    close(fd);

    remove(filename);
}

Test(serialize_thread_list, serialization_test) {
    char filename[] = "temp_test_file_thread_list";
    int fd = creat(filename, 0644);

    comment_t comment1 = {.uuid = "comment1_uuid", .content = "Comment1 content", .author_uuid = "author1_uuid"};
    comment_t comment2 = {.uuid = "comment2_uuid", .content = "Comment2 content", .author_uuid = "author2_uuid"};
    comment_t comment3 = {.uuid = "comment3_uuid", .content = "Comment3 content", .author_uuid = "author3_uuid"};

    comment_list_t comments1 = {.first = &comment1};
    comment1.next = &comment2;
    comment2.next = &comment3;
    comment3.next = NULL;

    thread_t thread1 = {
        .uuid = "thread1_uuid",
        .title = "Thread 1 title",
        .content = "Thread 1 content",
        .comments = &comments1,
        .next = NULL
    };

    comment_t comment4 = {.uuid = "comment4_uuid", .content = "Comment4 content", .author_uuid = "author4_uuid"};
    comment_t comment5 = {.uuid = "comment5_uuid", .content = "Comment5 content", .author_uuid = "author5_uuid"};

    comment_list_t comments2 = {.first = &comment4};
    comment4.next = &comment5;
    comment5.next = NULL;

    thread_t thread2 = {
        .uuid = "thread2_uuid",
        .title = "Thread 2 title",
        .content = "Thread 2 content",
        .comments = &comments2,
        .next = NULL
    };

    thread_list_t list = {.first = &thread1};
    thread1.next = &thread2;

    serialize_thread_list(fd, &list);

    close(fd);

    fd = open(filename, O_RDONLY);

    thread_list_t read_list;
    read(fd, &read_list, sizeof(thread_list_t));
    cr_assert_not_null(read_list.first, "Serialized thread list is NULL");

    thread_t *tmp = read_list.first;

    cr_assert_str_eq(tmp->uuid, "thread1_uuid", "Serialized thread1 UUID incorrect");
    cr_assert_str_eq(tmp->title, "Thread 1 title", "Serialized thread1 title incorrect");
    cr_assert_str_eq(tmp->content, "Thread 1 content", "Serialized thread1 content incorrect");

    comment_t *tmp_comment = tmp->comments->first;
    cr_assert_str_eq(tmp_comment->uuid, "comment1_uuid", "Serialized comment1 UUID of thread1 incorrect");
    cr_assert_str_eq(tmp_comment->content, "Comment1 content", "Serialized comment1 content of thread1 incorrect");

    tmp_comment = tmp_comment->next;
    cr_assert_str_eq(tmp_comment->uuid, "comment2_uuid", "Serialized comment2 UUID of thread1 incorrect");
    cr_assert_str_eq(tmp_comment->content, "Comment2 content", "Serialized comment2 content of thread1 incorrect");

    tmp_comment = tmp_comment->next;
    cr_assert_str_eq(tmp_comment->uuid, "comment3_uuid", "Serialized comment3 UUID of thread1 incorrect");
    cr_assert_str_eq(tmp_comment->content, "Comment3 content", "Serialized comment3 content of thread1 incorrect");

    tmp = tmp->next;

    cr_assert_str_eq(tmp->uuid, "thread2_uuid", "Serialized thread2 UUID incorrect");
    cr_assert_str_eq(tmp->title, "Thread 2 title", "Serialized thread2 title incorrect");
    cr_assert_str_eq(tmp->content, "Thread 2 content", "Serialized thread2 content incorrect");

    tmp_comment = tmp->comments->first;
    cr_assert_str_eq(tmp_comment->uuid, "comment4_uuid", "Serialized comment4 UUID of thread2 incorrect");
    cr_assert_str_eq(tmp_comment->content, "Comment4 content", "Serialized comment4 content of thread2 incorrect");

    tmp_comment = tmp_comment->next;
    cr_assert_str_eq(tmp_comment->uuid, "comment5_uuid", "Serialized comment5 UUID of thread2 incorrect");
    cr_assert_str_eq(tmp_comment->content, "Comment5 content", "Serialized comment5 content of thread2 incorrect");

    close(fd);
    remove(filename);
}