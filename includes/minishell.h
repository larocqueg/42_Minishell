/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:44:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/29 15:42:41 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

typedef enum e_type
{
	WORD,
	PIPE,
	HERE_DOC,
	APPEND,
	INFILE,
	TOFILE,
	VAR,
}	t_type;

typedef struct s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
	bool			to_pipe;
	bool			from_pipe;
	int				fd_in;
	int				fd_out;

}	t_cmd;

typedef struct s_shell
{
	int		from_fd;
	int		to_fd;
	char	*cli_text;
	char	**envp;
	t_cmd	*cmd;
	int		*pipe_old;
	int		*pipe_new;
	int		original_stdout;
	int		original_stdin;
	int		DEBUG;
}	t_shell;

typedef struct s_token
{
	char			*token;
	t_type			type;
	bool			expand;
	struct s_token	*next;
}	t_token;

typedef struct s_fd
{
	int	fd_in;
	int	fd_out;
}	t_fd;

extern int	g_exit_code;

//tokens
t_token	*tokenize(char *str, t_shell *sh);
t_token	*ft_tokennew(char *str, int type);
void	ft_token_addback(t_token **token, t_token *new_token);
int		is_space(char prompt);
int		is_operator(char prompt);
char	*ft_insertstr(char	*string, int index, char *substr);
void	expand_tokens(t_token *token);
void	create_cmds(t_shell *sh, t_token *token);
void	execute(t_shell *sh);

//cli
int		start_cli(t_shell *sh);
void	get_cli_pwd(t_shell *sh);

# define PROGRAM_NAME RED"minihell "RESET
//colors
# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define MAGENTA "\033[35m"

#endif
