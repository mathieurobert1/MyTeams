##
## EPITECH PROJECT, 2024
## MyTeams
## File description:
## Makefile of the project
##

SRC = 		server/src/parsing.c 				\
			server/src/lists/channels_list.c	\
			server/src/lists/clients_list.c 	\
			server/src/lists/teams_list.c 		\
			server/src/lists/threads_list.c 	\
			server/src/lists/users_list.c 		\
			server/src/lists/messages_list.c 	\
			server/src/lists/comment_list.c 	\
			server/src/init_server.c 			\
			server/src/server.c 				\
			server/src/accept_connection.c 	\
			server/src/delete_server.c 		\
			\
			server/src/commands/commands.c 		\
			server/src/commands/handle_commands.c 	\
			server/src/commands/read_command.c 	\
			\
			server/src/commands/help.c 		\
			server/src/commands/login.c 		\
			server/src/commands/logout.c 		\
			server/src/commands/users.c 		\
			server/src/commands/user.c 		\
			server/src/commands/send.c 		\
			server/src/commands/messages.c 	\
			server/src/commands/subscribe.c 	\
			server/src/commands/subscribed/subscribed.c 	\
			server/src/commands/subscribed/subscribed_utils.c 	\
			server/src/commands/unsubscribe.c 	\
			server/src/commands/use.c 			\
			server/src/commands/create/create.c 		\
			server/src/commands/create/create_team.c 		\
			server/src/commands/create/create_channel.c	\
			server/src/commands/create/create_thread.c	\
			server/src/commands/create/create_reply.c	\
			server/src/commands/list/list.c 		\
			server/src/commands/list/channels.c 		\
			server/src/commands/list/replys.c 		\
			server/src/commands/list/threads.c 		\
			server/src/commands/info.c 		\
			server/src/commands/use_utils.c	\
			server/src/commands/utils/uuid.c	\
			server/src/commands/utils/command.c	\
			server/src/commands/utils/get_instance.c	\
			server/src/commands/utils/print_instance.c	\
			\
			server/src/protocol/send.c 		\
			\
			server/src/data/save.c				\
			server/src/data/load.c				\
			server/src/data/serialization/channel.c\
			server/src/data/serialization/message.c\
			server/src/data/serialization/server.c\
			server/src/data/serialization/team.c\
			server/src/data/serialization/thread.c\
			server/src/data/serialization/user.c\
			server/src/data/serialization/string.c\
			server/src/data/serialization/comment.c\
			server/src/data/deserialization/channel.c\
			server/src/data/deserialization/message.c\
			server/src/data/deserialization/server.c\
			server/src/data/deserialization/team.c\
			server/src/data/deserialization/thread.c\
			server/src/data/deserialization/user.c\
			server/src/data/deserialization/string.c\
			server/src/data/deserialization/comment.c\
			\
			\
			shared/get_command.c	\

OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
INC = -I./include -I./shared/include -I./libs/myteams/ -L ./libs/myteams/\
-lmyteams -luuid -I./server/include -I.

TEST_FILES = server/test_accept_connection.c	\

TEST_DIR = tests/
TEST = $(addprefix $(TEST_DIR), $(TEST_FILES))
TEST_OBJ = $(TEST:.c=.o)
TEST_GCNO = $(SRC:.c=.gcno)
TEST_GCDA = $(SRC:.c=.gcda)
TEST_FLAGS = $(CFLAGS) --coverage -lcriterion

TEST_NAME = test

SERVER_PATH = server/
CLI_PATH = cli/

SERVER_BIN = myteams_server
CLI_BIN = myteams_cli

all:
	$(MAKE) -C server
	$(MAKE) -C cli
	cp $(SERVER_PATH)$(SERVER_BIN) .
	cp $(CLI_PATH)$(CLI_BIN) .

clean:
	$(MAKE) clean -C server
	$(MAKE) clean -C cli
	rm -f $(OBJ) $(TEST_OBJ) $(TEST_GCNO) $(TEST_GCDA)

fclean:
	$(MAKE) fclean -C server
	$(MAKE) fclean -C cli
	rm -f $(SERVER_BIN) $(CLI_BIN)
	rm -f $(OBJ) $(TEST_OBJ) $(TEST_GCNO) $(TEST_GCDA)

re: fclean all

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INC)

test_obj: $(TEST_OBJ)

obj: $(OBJ)

tests_run: fclean
	$(MAKE) obj CFLAGS+=--coverage
	$(MAKE) test_obj
	$(CC) -o $(TEST_NAME) $(OBJ) $(SHARED_OBJ) $(TEST_OBJ) $(TEST_FLAGS) $(INC)
	./$(TEST_NAME)
	gcovr --exclude tests/
	gcovr -b --exclude tests/
