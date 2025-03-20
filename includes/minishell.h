/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:44:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/20 21:00:03 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libs/libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

# define CMD=0
# define PIPE=1
# define HERE_DOC=2
# define APPEND=3
# define INFILE=4
# define TOFILE=5
# define PIPE=6
# define ARG=7

typedef	struct s_shell
{
	int		from_fd;
	int		to_fd;

	char	**envp;
}	t_shell;

typedef struct s_token
{
	char	*token;
	int		type;
	s_token *next;

}	t_token;

//functions

#endif
