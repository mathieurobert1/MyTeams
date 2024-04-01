/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** main
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <signal.h>
#include "client.h"


int main(int ac, char **av) {
    client_t client;
    int ret = 0;;

    ret = parse_client(ac, av, &client);
    if (ret != 0) {
        if (ret == 1)
            return 0;
        return ret;
    }
    free(client->ip);
    return ret;
}

// int main(int ac, char **av)
// {
//     (void) ac;
//     (void) av;
//     int domain = AF_INET;
//     int type = SOCK_STREAM;
//     int protocol = 0;
//     struct sockaddr_in serveraddr;
//     int cli_fd = 0;
//     fd_set rdfds;
//     fd_set wrtfds;
 
//     cli_fd = socket(domain, type, protocol);
//     if (!cli_fd) {
//         perror("socket failed");
//         exit(84);
//     }
//     serveraddr.sin_family = domain;
//     serveraddr.sin_port = htons(8888);
//     serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//     int len = sizeof(serveraddr);
//     if (connect(cli_fd, (struct sockaddr *)&serveraddr, len) != 0) {
//         perror("connection failed");
//         exit(84);
//     }
//     while (1) {
//         FD_ZERO(&wrtfds);
//         FD_ZERO(&rdfds);        
//         FD_SET(cli_fd, &rdfds);
//         FD_SET(cli_fd, &wrtfds);
//         select(cli_fd + 1, &rdfds, &wrtfds, NULL, NULL);
//         if (FD_ISSET(cli_fd, &rdfds)) {
//             // printf("read triggered");
//         }
//         if (FD_ISSET(cli_fd, &wrtfds)) {
//             // printf("write triggered");
//         }
//     }
//     close(cli_fd);
//     return 0;
// }
