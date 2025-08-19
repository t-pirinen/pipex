

NAME = pipex
LIB = header/libpipex.h

CC = cc -Wall -Wextra -Werror

LIBFT = libft/libft.a

SRC_PATH = src/
OBJ_PATH = obj/

SRC = main.c child_1.c child_2.c arg_validation.c	\
		get_cmd_path.c get_paths.c pipe_and_fork.c	\
		waitpid_fail.c frees_and_close.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJ_PATH) $(LIBFT) $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) -c $^ -o $@

$(LIBFT):
	@make -C libft -s

$(NAME): $(OBJS) $(LIB)
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)
	make clean -C libft -s

fclean:
	rm -rf $(OBJ_PATH)
	rm -rf $(NAME)
	make fclean -C libft -s

re: clean all

.SECONDARY: $(OBJS) $(LIB)
.PHONY: all clean fclean re
