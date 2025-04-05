# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 18:29:47 by gde-la-r          #+#    #+#              #
#    Updated: 2025/04/05 12:03:21 by rafaelfe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# The name of the lib
NAME = libftfprintf.a

# Compiler
CC = cc

# Compiling flags
CFLAGS = -Wall -Wextra -Werror

INCLUDES_DIR = .  # Points to the directory containing libft.h

# Source files
SRCS = ft_fprintf.c ft_fputchar.c ft_fputnbr_base.c ft_fputpointer.c ft_fputstr.c ft_fstrchar.c

# Object files
OBJS = $(SRCS:.c=.o)

# all rule
all: $(NAME)

# Compile the lib
# ar creates/modify libft.a
# r tells ar to  insert OBJS into the libft.a, if it already exists it will replace same name files
# c tells ar to create the archive if it does not exist
# s creats a index for each function in libft.a
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Compile the object files
%.o: %.c
	$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@

# clean rule removes .o from srcs
clean:
	rm -rf $(OBJS)

# fclean rule runs clean then removes libft.a
fclean: clean
	rm -rf $(NAME)

# re rule runs fclean then runs make again
re: fclean
	make

# Avoid name clashes
.PHONY: all clean fclean re bonus

