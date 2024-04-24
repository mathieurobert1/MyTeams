/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** test_create
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <time.h>

#include "server/include/commands.h"
#include "server/include/server.h"
#include "server/include/lists.h"
#include "shared/include/protocol.h"

#define PORT_MIN 49152
#define PORT_MAX 65535

static int get_random_port() {
    return rand() % (PORT_MAX - PORT_MIN + 1) + PORT_MIN;
}

Test(create_command, test_create_with_use_state_none)
{
    srand(time(NULL) + 40);

    server_t *server = malloc(sizeof(server_t));
    cr_assert_not_null(server, "Failed to allocate memory for server");
    server->_port = get_random_port();
    cr_assert(init_server(server), "Failed to initialize server");

    client_t *client = malloc(sizeof(client_t));
    cr_assert_not_null(client, "Failed to allocate memory for client");
    client->_fd = 1;
    FD_SET(client->_fd, &server->writefds);

    client->_use_state = NONE;

    cr_redirect_stdout();

    create_command(NULL, server, client);

    cr_assert_stdout_eq_str("531 No context defined before: /use\r\n", "Expected output: 531 No context defined before: /use, Got: %s", cr_get_redirected_stdout());
}

// Test(create_command, test_create_with_use_state_empty)
// {
//     srand(time(NULL) + 50);

//     server_t *server = malloc(sizeof(server_t));
//     cr_assert_not_null(server, "Failed to allocate memory for server");
//     server->_port = get_random_port();
//     server->_list_teams = init_list_teams();
//     cr_assert(init_server(server), "Failed to initialize server");

//     client_t *client = malloc(sizeof(client_t));
//     cr_assert_not_null(client, "Failed to allocate memory for client");
//     user_list_t *user_list = init_list_users();
//     server->_list_users = user_list;
//     client->_user_data = create_user(user_list, "uuid", "username");
//     client->_fd = 1;
//     FD_SET(client->_fd, &server->writefds);

//     char **command = malloc(sizeof(char *) * 4);
//     command[0] = strdup("/create");
//     command[1] = strdup("team_name");
//     command[2] = strdup("team_description");
//     command[3] = NULL;

//     client->_use_state = EMPTY;

//     cr_redirect_stdout();

//     create_command(command, server, client);

//     cr_assert_stdout_eq_str("531 No context defined before: /use\r\n", "Expected output: 531 No context defined before: /use, Got: '%s'", cr_get_redirected_stdout());
// }
