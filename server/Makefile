##
## EPITECH PROJECT, 2024
## MyTeams
## File description:
## Makefile
##

MAIN_FILE = src/main.c

MAIN_OBJ = $(MAIN_FILE:.c=.o)

SRC_FILES = parsing.c 				\
			lists/channels_list.c	\
			lists/clients_list.c 	\
			lists/teams_list.c 		\
			lists/threads_list.c 	\
			lists/users_list.c 		\
			lists/messages_list.c 	\
			lists/comment_list.c 	\
			init_server.c 			\
			server.c 				\
			accept_connection.c 	\
			delete_server.c 		\
			\
			commands/commands.c 		\
			commands/handle_commands.c 	\
			commands/read_command.c 	\
			\
			commands/help.c 		\
			commands/login.c 		\
			commands/logout.c 		\
			commands/users.c 		\
			commands/user.c 		\
			commands/send.c 		\
			commands/messages.c 	\
			commands/subscribe.c 	\
			commands/subscribed/subscribed.c 	\
			commands/subscribed/subscribed_utils.c 	\
			commands/unsubscribe.c 	\
			commands/use.c 			\
			commands/create/create.c 		\
			commands/create/create_team.c 		\
			commands/create/create_channel.c	\
			commands/create/create_thread.c	\
			commands/create/create_reply.c	\
			commands/list/list.c 		\
			commands/list/channels.c 		\
			commands/list/replys.c 		\
			commands/list/threads.c 		\
			commands/info.c 		\
			commands/use_utils.c	\
			commands/utils/uuid.c	\
			commands/utils/command.c	\
			commands/utils/get_instance.c	\
			commands/utils/print_instance.c	\
			\
			protocol/send.c 		\
			\
			data/save.c				\
			data/load.c				\
			data/serialization/channel.c\
			data/serialization/message.c\
			data/serialization/server.c\
			data/serialization/team.c\
			data/serialization/thread.c\
			data/serialization/user.c\
			data/serialization/string.c\
			data/serialization/comment.c\
			data/deserialization/channel.c\
			data/deserialization/message.c\
			data/deserialization/server.c\
			data/deserialization/team.c\
			data/deserialization/thread.c\
			data/deserialization/user.c\
			data/deserialization/string.c\
			data/deserialization/comment.c\

SHARED_FILES = get_command.c \

SHARED_DIR = ../shared/
SHARED_SRC = $(addprefix $(SHARED_DIR), $(SHARED_FILES))
SHARED_OBJ = $(SHARED_SRC:.c=.o)

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
INC = -I./include -I../libs/myteams/ \
	-I../shared/include -L ../libs/myteams/ -lmyteams -luuid

TEST_FILES =

TEST_DIR = tests/
TEST = $(addprefix $(TEST_DIR), $(TEST_FILES))
TEST_OBJ = $(TEST:.c=.o)
TEST_GCNO = $(SRC:.c=.gcno)
TEST_GCDA = $(SRC:.c=.gcda)
TEST_FLAGS = $(CFLAGS) --coverage -lcriterion

NAME = myteams_server
TEST_NAME = test_server

CC = gcc

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ) $(SHARED_OBJ)
	$(CC) -o $(NAME) $(OBJ) $(SHARED_OBJ) $(MAIN_OBJ) $(CFLAGS) $(INC)

run: all
	./$(NAME)

clean:
	rm -f $(OBJ) $(MAIN_OBJ) $(TEST_OBJ) $(SHARED_OBJ) \
		$(TEST_GCNO) $(TEST_GCDA)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

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
