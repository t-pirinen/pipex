

NAME = pipex
LIB = header/libpipex.h

CC = cc -Wall -Wextra -Werror

LIBFT = libft/libft.a

SRC_PATH = src/
OBJ_PATH = obj/

SRC = child_1.c child_2.c frees_and_close.c main.c paths.c main_util.c
SRCS = $(addprefix src/, $(SRC))

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix obj/, $(OBJ))

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) -c $^ -o $@

$(LIBFT):
	make -C libft -s

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)
	make clean -C libft -s

fclean:
	rm -rf $(OBJ_PATH)
	rm -rf $(NAME)
	make fclean -C libft -s

re: clean all

.PHONY: all clean fclean re
