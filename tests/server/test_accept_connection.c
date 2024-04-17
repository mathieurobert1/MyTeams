/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** test_accept_connection
*/

#include "server/include/server.h" // accept_connection

#include <criterion/criterion.h>
#include <unistd.h> // fork, close
#include <sys/socket.h> //  socket, bind, listen, accept, connect
#include <netinet/in.h> //  sockaddr_in
#include <arpa/inet.h> //  htons
#include <stdio.h> //  perror
#include <stdlib.h> //  exit, EXIT_*
#include <errno.h> //  errno
#include <sys/wait.h> //  waitpid
#include <time.h> //  time

#define PORT_MIN 49152
#define PORT_MAX 65535

int get_random_port() {
    return rand() % (PORT_MAX - PORT_MIN + 1) + PORT_MIN;
}

Test(accept, test_valid_command) {
    srand(time(NULL));

    server_t *server = malloc(sizeof(server_t));
    cr_assert_not_null(server, "Failed to allocate memory for server");

    server->_port = get_random_port();
    cr_assert(init_server(server), "Failed to initialize server");

    int server_port = ntohs(server->_addr.sin_port);

    int pid = fork();
    if (pid == 0) {
        close(server->_fd);

        int client_fd = socket(AF_INET, SOCK_STREAM, 0);
        cr_assert(client_fd >= 0, "Failed to create client socket");

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        server_addr.sin_port = htons(server_port);
        cr_assert(connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0, "Failed to connect to server");

        close(client_fd);
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        int status;
        printf("PID: %d\n", pid);
        waitpid(pid, &status, 0);

        cr_assert(WIFEXITED(status), "Child process did not exit normally");
        cr_assert_eq(WEXITSTATUS(status), EXIT_SUCCESS, "Child process exited with failure");

        int max_fd = 0;
        FD_ZERO(&server->readfds);
        FD_ZERO(&server->writefds);
        FD_SET(server->_fd, &server->readfds);
        accept_connection(server, &max_fd);
        cr_assert_eq(server->_list_client->nb_client, 1, "Failed to accept connection, nb_client: %d", server->_list_client->nb_client);

        close(server->_fd);
    } else {
        perror("fork");
        cr_assert_fail("fork failed");
    }
}

Test(accept, test_with_bad_fd)
{
    srand(time(NULL) + 10);

    server_t *server = malloc(sizeof(server_t));
    cr_assert_not_null(server, "Failed to allocate memory for server");

    server->_port = get_random_port();
    cr_assert(init_server(server), "Failed to initialize server");

    int max_fd = 0;
    FD_ZERO(&server->readfds);
    FD_ZERO(&server->writefds);
    server->_fd = -1;
    FD_SET(server->_fd, &server->readfds);
    accept_connection(server, &max_fd);
    cr_assert_eq(server->_list_client->nb_client, 0, "Failed to accept connection, nb_client: %d", server->_list_client->nb_client);

    close(server->_fd);
}

Test(accept, test_with_fd_not_set)
{
    srand(time(NULL) + 20);

    server_t *server = malloc(sizeof(server_t));
    cr_assert_not_null(server, "Failed to allocate memory for server");

    server->_port = get_random_port();
    cr_assert(init_server(server), "Failed to initialize server");

    int max_fd = 0;
    FD_ZERO(&server->readfds);
    FD_ZERO(&server->writefds);
    accept_connection(server, &max_fd);
    cr_assert_eq(server->_list_client->nb_client, 0, "Failed to accept connection, nb_client: %d", server->_list_client->nb_client);

    close(server->_fd);
}

Test(accept, test_with_big_max_fd)
{
    srand(time(NULL) + 30);

    server_t *server = malloc(sizeof(server_t));
    cr_assert_not_null(server, "Failed to allocate memory for server");

    server->_port = get_random_port();
    cr_assert(init_server(server), "Failed to initialize server");

    int server_port = ntohs(server->_addr.sin_port);

    int pid = fork();
    if (pid == 0) {
        close(server->_fd);

        int client_fd = socket(AF_INET, SOCK_STREAM, 0);
        cr_assert(client_fd >= 0, "Failed to create client socket");

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        server_addr.sin_port = htons(server_port);
        cr_assert(connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0, "Failed to connect to server");

        close(client_fd);
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        int status;
        printf("PID: %d\n", pid);
        waitpid(pid, &status, 0);

        cr_assert(WIFEXITED(status), "Child process did not exit normally");
        cr_assert_eq(WEXITSTATUS(status), EXIT_SUCCESS, "Child process exited with failure");

        int max_fd = 2147483647;
        FD_ZERO(&server->readfds);
        FD_ZERO(&server->writefds);
        FD_SET(server->_fd, &server->readfds);
        accept_connection(server, &max_fd);
        cr_assert_eq(server->_list_client->nb_client, 1, "Failed to accept connection, nb_client: %d", server->_list_client->nb_client);

        close(server->_fd);
    } else {
        perror("fork");
        cr_assert_fail("fork failed");
    }
}
