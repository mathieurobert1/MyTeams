/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** data
*/

#pragma once

#include "types.h"

/**
 * @brief save all the data containing on server_t
 *
 * @param server data to save
 */
void data_save(server_t *server);

/**
 * @brief load all the data saving before in server_t
 *
 * @return server_t*
 */
server_t *data_load(void);

/**
 * @brief serialize a channel_list_ struct
 *
 * @param fd
 * @param list
 */
void serialize_channel_list(int fd, channel_list_t *list);

/**
 * @brief serialize a channel struct
 *
 * @param fd
 * @param channel
 */
void serialize_channel(int fd, channel_t *channel);

/**
 * @brief serialize a message_list_t struct
 *
 * @param fd
 * @param list
 */
void serialize_message_list(int fd, message_list_t *list);

/**
 * @brief serialize a message_t struct
 *
 * @param fd
 * @param message
 */
void serialize_message(int fd, message_t *message);

/**
 * @brief serialize a user_list_t struct
 *
 * @param fd
 * @param list
 */
void serialize_user_list(int fd, user_list_t *list);

/**
 * @brief serialize a user_t struct
 *
 * @param fd
 * @param user
 */
void serialize_user(int fd, user_t *user);

/**
 * @brief serialize a thread_list_t struct
 *
 * @param fd
 * @param list
 */
void serialize_thread_list(int fd, thread_list_t *list);

/**
 * @brief serialize a thread_t struct
 *
 * @param fd
 * @param thread
 */
void serialize_thread(int fd, thread_t *thread);

/**
 * @brief serialize a team_list_t struct
 *
 * @param fd
 * @param list
 */
void serialize_team_list(int fd, team_list_t *list);

/**
 * @brief serialize a team_t struct
 *
 * @param fd
 * @param team
 */
void serialize_team(int fd, team_t *team);

/**
 * @brief serialize a server_t struct
 *
 * @param fd
 * @param server
 */
void serialize_server(int fd, server_t *server);

/**
 * @brief serialize a string
 *
 * @param fd
 * @param str
 */
void serialize_string(int fd, char *str);

/**
 * @brief serialize a comment_t struct
 *
 * @param fd the file descriptor
 * @param comment the comment to serialize
 */
void serialize_comment(int fd, comment_t *comment);

/**
 * @brief serialize a comment_litst_t struct
 *
 * @param fd the file descriptor
 * @param list the list to serialize
 */
void serialize_comment_list(int fd, comment_list_t *list);

/**
 * @brief deserialize a channel_list_t struct
 *
 * @param fd
 * @return channel_list_t*
 */
channel_list_t *deserialize_channel_list(int fd);

/**
 * @brief deserialize a channel_t struct
 *
 * @param fd
 * @return channel_t*
 */
channel_t *deserialize_channel(int fd);

/**
 * @brief deserialize a message_list_t struct
 *
 * @param fd
 * @return message_list_t*
 */
message_list_t *deserialize_message_list(int fd);

/**
 * @brief deserialize a message_t struct
 *
 * @param fd
 * @return message_t*
 */
message_t *deserialize_message(int fd);

/**
 * @brief deserialize a user_list_t struct
 *
 * @param fd
 * @return user_list_t*
 */
user_list_t *deserialize_user_list(int fd);

/**
 * @brief deserialize a user_t struct
 *
 * @param fd
 * @return user_t*
 */
user_t *deserialize_user(int fd);

/**
 * @brief deserialize a thread_list_t struct
 *
 * @param fd
 * @return thread_list_t*
 */
thread_list_t *deserialize_thread_list(int fd);

/**
 * @brief deserialize a thread_t struct
 *
 * @param fd
 * @return thread_t*
 */
thread_t *deserialize_thread(int fd);

/**
 * @brief deserialize a team_list_t struct
 *
 * @param fd
 * @return team_list_t*
 */
team_list_t *deserialize_team_list(int fd);

/**
 * @brief deserialize a team_t struct
 *
 * @param fd
 * @return team_t*
 */
team_t *deserialize_team(int fd);

/**
 * @brief deserialize a server_t struct
 *
 * @param fd
 * @return server_t*
 */
server_t *deserialize_server(int fd);

/**
 * @brief deserialize a string
 *
 * @param fd
 * @return char*
 */
char *deserialize_string(int fd);
