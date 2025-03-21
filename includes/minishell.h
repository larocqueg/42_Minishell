/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:44:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/21 02:29:59 by rafaelfe         ###   ########.fr       */
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

# define CMD 0
# define PIPE 1
# define HERE_DOC 2
# define APPEND 3
# define INFILE 4
# define TOFILE 5
# define PIPE 6
# define ARG 7
# define SINGLEQ_ARG 8
# define FILE 9

typedef	struct s_shell
{
	int		from_fd;
	int		to_fd;
	char	*cli_text;
	char	**envp;
}	t_shell;

typedef struct s_token
{
	char	*token;
	int		type;
	bool	builtin;
	struct s_token *next;

}	t_token;
//functions


//cli
int		start_cli(t_shell *sh);
void	get_cli_pwd(t_shell *sh);

#define PROGRAM_NAME RED"minihell "RESET
#define COLOR_STRING(COLOR, str) COLOR str RESET
//colors
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"

#endif
