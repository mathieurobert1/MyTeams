##
## EPITECH PROJECT, 2024
## MyTeams
## File description:
## Makefile
##

MAIN_FILE = src/main.c

MAIN_OBJ = $(MAIN_FILE:.c=.o)

SRC_FILES = parsing.c \
			init_server.c \
			server.c \

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
INC = -I./include

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

$(NAME): $(OBJ) $(MAIN_OBJ)
	$(CC) -o $(NAME) $(OBJ) $(MAIN_OBJ) $(CFLAGS) $(INC)

run: all
	./$(NAME)

clean:
	rm -f $(OBJ) $(MAIN_OBJ) $(TEST_OBJ) $(TEST_GCNO) $(TEST_GCDA)

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
	$(CC) -o $(TEST_NAME) $(OBJ) $(TEST_OBJ) $(TEST_FLAGS) $(INC)
	./$(TEST_NAME)
	gcovr --exclude tests/
	gcovr -b --exclude tests/