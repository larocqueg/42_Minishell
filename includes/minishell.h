/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:44:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/15 22:09:39 by rafaelfe         ###   ########.fr       */
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
# include <limits.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>

//constants
# define ARG_MAX 2097152

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
	bool			infile_error;
	bool			tofile_error;
	bool			heredoc;
}	t_cmd;

typedef struct s_token
{
	char			*token;
	t_type			type;
	bool			expand;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	char	*prompt;
	char	*cli_text;
	int		env_size;
	char	**envp;
	int		local_size;
	char	**local_vars;
	t_cmd	*cmd;
	t_token	*token;
	int		*pipe_old;
	int		*pipe_new;
	int		original_stdout;
	int		original_stdin;
	int		heredoc_count;
	int		**heredoc_pipes;
	int		exit_code;
}	t_shell;

typedef struct s_fd
{
	int	fd_in;
	int	fd_out;
}	t_fd;

//tokens
int		tokenize(char *str, t_shell *sh);
t_token	*ft_tokennew(char *str, int type);
void	ft_token_addback(t_token **token, t_token *new_token);
int		is_space(char prompt);
int		is_operator(char prompt);
char	*ft_insertstr(char	*string, size_t index, char *substr);
//heredoc
int		get_heredoc(t_shell *sh);
int		is_var(char *token);

//expand
char	*expand(char *str, t_shell *sh, bool heredoc);
void	expand_tokens(t_shell *sh);
char	*extract_variable(char *str, int i);
int		ft_is_all_var(char	*str);
char	*ft_expand_string(char *str, size_t *i, t_shell *sh);
char	*ft_expand_exit(char *str, size_t *i);
char	*ft_expand_vars(char *str, size_t *i, t_shell *sh);

//builtin_utils.c
void	ft_swap(char **s1, char **s2);
int		ft_strcmp_tochar(const char *s1, const char *s2, char c);
char	**clone_envp(t_shell *sh, char **envp);
size_t	ft_strlen_tochar(char *str, char c);
char	**append_cmd(char **cmd, char *newcmd);
int		get_argc(char **cmd);

//env.c
void	ft_print_env(t_shell *sh);

//export.c
void	print_export(t_shell *sh);
char	*remove_quotes(char *str);
int		ft_find_var(char *new_var, char **envp);

//error handling
int		check_quotes(char *prompt);
int		check_tokens(t_token *token);
int		check_syntax(t_shell *sh);

//cli
int		start_cli(t_shell *sh);
void	get_cli_pwd(t_shell *sh);
t_shell *ft_get_sh(bool set, t_shell *sh);

//free_utils
void	ft_free(char **str);
void	free_cmds(t_shell *sh);
void	free_tokens(t_token *token);
void	free_envp(t_shell *sh);
void	free_pipes(t_shell *sh);

//cmds
int		create_cmds(t_shell *sh);
t_token	*getfd_tofile(t_token *token, t_cmd *newcmd);
t_token	*getfd_infile(t_token *token, t_cmd *newcmd);
t_token	*getfd_append(t_token *token, t_cmd *newcmd);
t_token	*getfd_heredoc(t_token *token, t_cmd *newcmd, t_shell *sh);
t_token	*get_command(t_token *token, t_cmd *newcmd);
int		perm_error(t_cmd *cmd);
void	ft_free_until_cmds(t_shell *sh);

//execute
void	execute(t_shell *sh);
void	change_pipes(t_shell *sh, t_cmd *cmd);
int		fork_cmd(t_shell *sh, t_cmd *cmd, int *pid);
int		create_pipe(t_shell *sh, t_cmd *cmd);
int		get_fdin(t_cmd *cmd, t_shell *sh);
int		get_fdout(t_cmd *cmd, t_shell *sh);
void	ft_command_error(t_cmd *cmd, char *path, char **cmds, t_shell *sh);
void	exec_cmd(t_cmd *cmds, char **env, t_shell *sh);

//path_finder
char	*local_path_finder(char *cmd, bool from_path_finder);
char	*path_finder(char *cmds, char **env);
int		is_file(char *path);
int		is_folder(char *path);
int		is_character_device(const char *path);

//built ins!
void	exec_pwd(t_cmd *cmd);
void	exec_export(t_shell *sh, t_cmd *cmd);
int		exec_cd(char **cmd, t_shell *sh);
void	exec_exit(t_shell *sh, t_cmd *cmds);
void	exec_echo(t_cmd *cmds);
void	exec_unset(t_shell *sh, char **cmd);
void	free_builtin(t_cmd *cmd, t_shell *sh);
void	exec_builtin(t_cmd *cmd, t_shell *sh);
void	exec_env(t_shell *sh, t_cmd *cmd);
int		ft_is_builtin(char **cmds);
void	handle_perm_error(t_cmd *cmd, t_shell *sh);

//env cmds
char	*ft_get_env(char *var_name, char **env);
void	ft_change_var(char *var_name, char *content, char **env);

//signals
int		ft_exit_status(int exit_code, bool set, bool close);
void	signal_handler(int sig);
void	signal_default(void);
void	child_signal_handler(int sig);

//error messages
# define UNEXPECTED_T "minishell: syntax error: unexpected token"
# define REDIRECT_T "minishell: Expected argument after"

#endif
