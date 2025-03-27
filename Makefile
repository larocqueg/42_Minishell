# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 15:21:10 by gde-la-r          #+#    #+#              #
#    Updated: 2025/03/27 17:07:29 by rafaelfe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output name
NAME = minishell

# Compilation
CC = cc
#CFLAGS = -Wall -Wextra -Werror -g
CFLAGS = -g
LDFLAGS= -lreadline -lncurses
# Paths
SRC_DIR = ./srcs
INCLUDES = ./includes
LIBFT_DIR = ./libs/libft

# Sources
SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/cli/cli.c \
	$(SRC_DIR)/cli/get_pwd.c \
	$(SRC_DIR)/parsing/tokenize.c \
	$(SRC_DIR)/parsing/token_utils.c \
	$(SRC_DIR)/parsing/expand.c \
	$(SRC_DIR)/parsing/expand_utils.c \
	$(SRC_DIR)/execute/cmds.c \
	$(SRC_DIR)/execute/execute.c \


# Objects
OBJS = $(SRC:.c=.o)
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)
	@echo "✅ Successfully built $(NAME)!"

$(LIBFT):
	@make -C $(LIBFT_DIR) --silent

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -I $(LIBFT_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT_DIR) --silent
	@clear
	@echo "✅ clean completed successfully!"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR) --silent
	@echo "✅ fclean completed successfully!"

re: fclean
	@make all
	@echo "✅ minishell successfully rebuilt!"i

run: re
	@./minishell

.PHONY: all clean fclean re
