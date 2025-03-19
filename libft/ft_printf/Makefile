# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gde-la-r <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 18:29:47 by gde-la-r          #+#    #+#              #
#    Updated: 2024/11/11 17:46:26 by gde-la-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# The name of the lib
NAME = libftprintf.a

# Compiler
CC = cc

# Compiling flags
CFLAGS = -Wall -Wextra -Werror

INCLUDES_DIR = .  # Points to the directory containing libft.h

# Source files
SRCS = ft_printf.c ft_putchar.c ft_putnbr_base.c ft_putpointer.c ft_putstr.c ft_strchar.c

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

