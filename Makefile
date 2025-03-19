NAME= minishell
CC= cc
CFLAGS = -g -Wall -Werror -Wextra -I $(INCLUDES)
LDFLAGS = -lreadline
INCLUDES= ./includes
SRCS_DIR= ./srcs
SRCS= $(SRCS_DIR)/main.c
OBJS= $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

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

