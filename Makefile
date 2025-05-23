# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/14 15:21:10 by gde-la-r          #+#    #+#              #
#    Updated: 2025/05/01 21:27:52 by rafaelfe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Output name
NAME = minishell
BONUS_NAME = minishell_bonus
# Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS= -lreadline -lncurses
# Paths
SRC_DIR = ./mandatory/srcs
INCLUDES = ./mandatory/includes
LIBFT_DIR = ./libs/libft
BONUS_DIR = ./bonus/srcs
BONUS_INCLUDES = ./bonus/includes

#Colors
RED    := \033[1;38;5;196m
GREEN  := \033[1;38;5;46m
NC  := \033[0m

# Sources
SRC = $(SRC_DIR)/main.c \
	$(SRC_DIR)/cli/cli.c \
	$(SRC_DIR)/parsing/tokenize.c \
	$(SRC_DIR)/parsing/token_utils.c \
	$(SRC_DIR)/parsing/expand.c \
	$(SRC_DIR)/parsing/token_last.c \
	$(SRC_DIR)/parsing/expand_utils.c \
	$(SRC_DIR)/parsing/string_utils.c \
	$(SRC_DIR)/parsing/syntax_check.c \
	$(SRC_DIR)/parsing/heredoc.c \
	$(SRC_DIR)/parsing/heredoc_utils.c \
	$(SRC_DIR)/execute/cmds.c \
	$(SRC_DIR)/execute/cmd_utils.c \
	$(SRC_DIR)/execute/get_fds.c \
	$(SRC_DIR)/execute/exec_builtin.c \
	$(SRC_DIR)/execute/exec_errors.c \
	$(SRC_DIR)/execute/exec_cmd.c \
	$(SRC_DIR)/execute/execute_pipe_utils.c \
	$(SRC_DIR)/execute/execute_utils.c \
	$(SRC_DIR)/execute/path_finder.c \
	$(SRC_DIR)/execute/execute.c \
	$(SRC_DIR)/builtin/builtin_utils.c \
	$(SRC_DIR)/builtin/cd.c \
	$(SRC_DIR)/builtin/pwd.c \
	$(SRC_DIR)/builtin/exit.c \
	$(SRC_DIR)/builtin/echo.c \
	$(SRC_DIR)/builtin/unset.c \
	$(SRC_DIR)/builtin/env.c \
	$(SRC_DIR)/builtin/export.c \
	$(SRC_DIR)/builtin/export_utils.c \
	$(SRC_DIR)/builtin/export_utils_2.c \
	$(SRC_DIR)/env/env_utils.c \
	$(SRC_DIR)/env/print_env.c \
	$(SRC_DIR)/signals/exit_status.c \
	$(SRC_DIR)/signals/signal_handler.c \
	$(SRC_DIR)/free_utils/free_array.c \
	$(SRC_DIR)/free_utils/free_cmds.c \
	$(SRC_DIR)/free_utils/free_tokens.c \
	$(SRC_DIR)/free_utils/free_heredoc.c \
	$(SRC_DIR)/free_utils/free_child.c \


BONUS_SRC = $(BONUS_DIR)/main_bonus.c \
	$(BONUS_DIR)/cli/cli_bonus.c \
	$(BONUS_DIR)/parsing/tokenize_bonus.c \
	$(BONUS_DIR)/parsing/token_utils_bonus.c \
	$(BONUS_DIR)/parsing/expand_bonus.c \
	$(BONUS_DIR)/parsing/token_last_bonus.c \
	$(BONUS_DIR)/parsing/expand_utils_bonus.c \
	$(BONUS_DIR)/parsing/string_utils_bonus.c \
	$(BONUS_DIR)/parsing/syntax_check_bonus.c \
	$(BONUS_DIR)/parsing/heredoc_bonus.c \
	$(BONUS_DIR)/parsing/heredoc_utils_bonus.c \
	$(BONUS_DIR)/execute/cmds_bonus.c \
	$(BONUS_DIR)/execute/cmd_utils_bonus.c \
	$(BONUS_DIR)/execute/get_fds_bonus.c \
	$(BONUS_DIR)/execute/exec_builtin_bonus.c \
	$(BONUS_DIR)/execute/exec_errors_bonus.c \
	$(BONUS_DIR)/execute/exec_cmd_bonus.c \
	$(BONUS_DIR)/execute/execute_pipe_utils_bonus.c \
	$(BONUS_DIR)/execute/execute_utils_bonus.c \
	$(BONUS_DIR)/execute/path_finder_bonus.c \
	$(BONUS_DIR)/execute/execute_bonus.c \
	$(BONUS_DIR)/execute/wild_card_bonus.c \
	$(BONUS_DIR)/builtin/builtin_utils_bonus.c \
	$(BONUS_DIR)/builtin/cd_bonus.c \
	$(BONUS_DIR)/builtin/pwd_bonus.c \
	$(BONUS_DIR)/builtin/exit_bonus.c \
	$(BONUS_DIR)/builtin/echo_bonus.c \
	$(BONUS_DIR)/builtin/unset_bonus.c \
	$(BONUS_DIR)/builtin/env_bonus.c \
	$(BONUS_DIR)/builtin/export_bonus.c \
	$(BONUS_DIR)/builtin/export_utils_bonus.c \
	$(BONUS_DIR)/builtin/export_utils_2_bonus.c \
	$(BONUS_DIR)/env/env_utils_bonus.c \
	$(BONUS_DIR)/env/print_env_bonus.c \
	$(BONUS_DIR)/signals/exit_status_bonus.c \
	$(BONUS_DIR)/signals/signal_handler_bonus.c \
	$(BONUS_DIR)/free_utils/free_array_bonus.c \
	$(BONUS_DIR)/free_utils/free_cmds_bonus.c \
	$(BONUS_DIR)/free_utils/free_tokens_bonus.c \
	$(BONUS_DIR)/free_utils/free_heredoc_bonus.c \
	$(BONUS_DIR)/free_utils/free_child_bonus.c \

# Objects
OBJS = $(SRC:.c=.o)
BONUS_OBJS = $(BONUS_SRC:.c=.o)
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)
bonus: $(BONUS_NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(NAME)
	@clear
	@echo "$(RED)\n\nooo        ooooo  o8o               o8o  ooooo   ooooo           oooo  oooo$(NC)"
	@echo "$(RED)\`88.       .888'  \`\"'               \`\"'  \`888'   \`888'           \`888  \`888$(NC)"
	@echo " $(RED)888b     d'888  oooo  ooo. .oo.   oooo   888     888   .ooooo.   888   888$(NC)"
	@echo " $(RED)8 Y88. .P  888  \`888  \`888P\"Y88b  \`888   888ooooo888  d88' \`88b  888   888$(NC)"
	@echo " $(RED)8  \`888'   888   888   888   888   888   888     888  888ooo888  888   888$(NC)"
	@echo " $(RED)8    Y     888   888   888   888   888   888     888  888    .o  888   888$(NC)"
	@echo "$(RED)o8o        o888o o888o o888o o888o o888o o888o   o888o \`Y8bod8P' o888o o888o\n\n$(NC)"
	@echo "✅ $(GREEN)Successfully built $(NAME)$(NC)!"

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -L$(LIBFT_DIR) -lft $(LDFLAGS) -o $(BONUS_NAME)
	@clear
	@echo "$(RED)\n\nooo        ooooo  o8o               o8o  ooooo   ooooo           oooo  oooo$(NC)"
	@echo "$(RED)\`88.       .888'  \`\"'               \`\"'  \`888'   \`888'           \`888  \`888$(NC)"
	@echo " $(RED)888b     d'888  oooo  ooo. .oo.   oooo   888     888   .ooooo.   888   888$(NC)"
	@echo " $(RED)8 Y88. .P  888  \`888  \`888P\"Y88b  \`888   888ooooo888  d88' \`88b  888   888$(NC)"
	@echo " $(RED)8  \`888'   888   888   888   888   888   888     888  888ooo888  888   888$(NC)"
	@echo " $(RED)8    Y     888   888   888   888   888   888     888  888    .o  888   888$(NC)"
	@echo "$(RED)o8o        o888o o888o o888o o888o o888o o888o   o888o \`Y8bod8P' o888o o888o.bonus\n\n$(NC)"
	@echo "✅ $(GREEN)Successfully built $(BONUS_NAME)$(NC)!"


$(LIBFT):
	@make -C $(LIBFT_DIR) --silent

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -I $(LIBFT_DIR) -c $< -o $@

$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	@$(CC) $(CFLAGS) -I $(BONUS_INCLUDES) -I $(LIBFT_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@rm -rf $(BONUS_OBJS)
	@make clean -C $(LIBFT_DIR) --silent
	@clear
	@echo "$(RED)clean completed successfully!$(NC)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS_NAME)
	@make fclean -C $(LIBFT_DIR) --silent
	@echo "$(RED)fclean completed successfully!$(NC)"

re: fclean
	@make all
	@echo "$(GREEN)minishell successfully rebuilt!$(NC)"

run: re
	@./minishell
debug: re
	@./minishell 1

.PHONY: all clean fclean re
