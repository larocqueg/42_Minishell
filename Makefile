NAME= minishell
CC= cc
CFLAGS = -g -Wall -Werror -Wextra -I $(INCLUDES)
INCLUDES= ./includes
SRCS_DIR= ./srcs
SRCS= $(SRCS_DIR)/main.c
OBJS= $(SRCS:.c=.o)

all: $(NAME)
	@echo "Project built, execute with ./minishell"

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c $^ -o $@

clean:
	@rm -rf $(OBJS)
	@echo "Cleaning Objects!"
fclean: clean
	@rm -rf $(NAME)
	@echo "Cleaning Objects and shell!"
re: fclean all

.PHONY: all clean fclean re

