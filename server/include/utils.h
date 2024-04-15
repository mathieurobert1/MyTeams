/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** utils
*/

#pragma once

#include "types.h"

#include <stdbool.h>

/**
 * @brief check if the command has too few arguments
 *
 * @param command user command
 * @param nb_args nb args required
 * @param fd_client client fd
 * @param writefds select variable to check if client can write
 * @return true
 * @return false
 */
bool is_too_few_args(char **command, size_t nb_args,
    int fd_client, fd_set *writefds);

/**
 * @brief check if the command has too more arguments
 *
 * @param command user command
 * @param nb_args nb args required
 * @param fd_client client fd
 * @param writefds select variable to check if client can write
 * @return true
 * @return false
 */
bool is_too_more_args(char **command, size_t nb_args,
    int fd_client, fd_set *writefds);

/**
 * @brief check if the command has the correct number of args
 *
 * @param command user command
 * @param nb_args nb args required
 * @param fd_client client fd
 * @param writefds select variable to check if client can write
 * @return true
 * @return false
 */
bool is_correct_command(fd_set *writefds, char **command,
    size_t nb_args, int fd_client);

/**
 * @brief check if use is define
 *
 * @param fd_client fd to write in case of error
 * @param writefds select variable to check if client can write
 * @param use_value the value to check
 * @return true
 * @return false
 */
bool is_context_def(int fd_client, fd_set *writefds, int use_value);

/**
 * @brief create an uuid
 *
 * @return char* of the uuid
 */
char *create_uuid(void);

/**
 * @brief get a team by its uuid
 *
 * @param uuid the uuid of the team to get
 * @param teams the list of teams
 * @return team_t*
 */
team_t *team_get_by_uuid(char *uuid, team_list_t *teams);

/**
 * @brief get a user by its uuid
 *
 * @param uuid the uuid of the user to get
 * @param users the list of users
 * @return user_t*
 */
user_t *user_get_by_uuid(char *uuid, user_list_t *users);

/**
 * @brief get a channel by its uuid
 *
 * @param uuid the uuid of the channel to get
 * @param channels the list of channels
 * @return channel_t*
 */
channel_t *channel_get_by_uuid(char *uuid, channel_list_t *channels);

/**
 * @brief get a thread by its uuid
 *
 * @param uuid the uuid of the thread to get
 * @param threads the list of threads
 * @return thread_t*
 */
thread_t *thread_get_by_uuid(char *uuid, thread_list_t *threads);

/**
 * @brief Get the str form of all teams
 * in format "CODE "team_uuid" "team_name"\n..."
 *
 * @param teams list of teams
 * @param fd file descriptor to write
 * @param writefds select variable to check if client can write
 */
void print_list_all_teams(team_list_t *teams, int fd, fd_set *writefds);

/**
 * @brief Get the str form of all channels
 * in format "CODE "thread_uuid" "thread_name" "thread_content"\n..."
 *
 * @param threads list of channels
 * @param fd file descriptor to write
 * @param writefds select variable to check if client can write
 */
void print_list_all_threads(thread_list_t *threads, int fd, fd_set *writefds);

/**
 * @brief Get the str form of list channels object
 * in format "CODE "channel_uuid" "channel_name"\n...
 * @param channels list of channels
 * @param fd file descriptor to write
 * @param writefds select variable to check if client can write
 */
void print_list_all_channels(channel_list_t *channels, int fd,
    fd_set *writefds);

/**
 * @brief Get the str form of list users object
 * in format "CODE "thread_uuid" "comment_uuid" "comment_timestamp"
 *      "comment_content"\n...
 * @param thread thread to get comments from
 * @param fd file descriptor to write
 * @param writefds select variable to check if client can write
 */
void print_list_all_comments(thread_t *thread, int fd, fd_set *writefds);
