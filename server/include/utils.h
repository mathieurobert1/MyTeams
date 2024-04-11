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
 * in format [team_name: team_uuid, ...]
 *
 * @param teams
 * @return char*
 */
char *get_str_list_all_teams(team_list_t *teams);

/**
 * @brief Get the str form of all channels
 * in format [channel_tittle: channel_uuid, ...]
 *
 * @param teams
 * @return char*
 */
char *get_str_list_all_threads(thread_list_t *threads);

/**
 * @brief Get the str form of list channels object
 * in format [channel_name: channel_uuid, ...]
 * @param channels
 * @return char*
 */
char *get_str_list_all_channels(channel_list_t *channels);
