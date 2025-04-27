/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:49:19 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/23 16:58:06 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "../../libs/libft/libft.h"
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
	bool			wildcard;
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
	int		*pids;
}	t_shell;

typedef struct s_fd
{
	int	fd_in;
	int	fd_out;
}	t_fd;

//main.c
void	ft_get_shlvl(t_shell *sh);
void	ft_init_pwd(t_shell *sh);
void	ft_sh_init(t_shell *sh, char **envp);

//cd.c
int		get_argc(char **cmd);
int		exec_cd(char **cmd, t_shell *sh);

//echo.c
void	exec_echo(t_cmd *cmd);

//unset.c
void	exec_unset(t_shell *sh, char **cmd);
int		ft_strcmp_unset(char *env, char *cmd);
char	**ft_free_back(char **new_env, int k);
char	**ft_get_unset(t_shell *sh, char **new_env, char **cmd, int k);
void	get_new_env(t_shell *sh, int *i, int *k, char **new_env);

//pwd.c
void	exec_pwd(t_cmd *cmd);

//env.c
void	exec_env(t_shell *sh, t_cmd *cmd);

//export.c
void	print_export(t_shell *sh);
void	exec_export(t_shell *sh, t_cmd *cmd);
void	create_export(char *str, t_shell *sh);
int		ft_strcmp_export(char **env, char *cmd);

//export_utils.c
int		is_append_var(char *str);
void	create_var(char *var_name, char *var, t_shell *sh);
void	append_var(char *var_name, char *var, char *temp, t_shell *sh);
void	do_append(char *var, t_shell *sh);
void	put_export(char *str);

//export_utils_2.c
void	ft_free_export(char **temp);

//builtin_utils.c
void	ft_swap(char **s1, char **s2);
int		ft_strcmp_tochar(const char *s1, const char *s2, char c);
size_t	ft_strlen_tochar(char *str, char c);
void	free_envp(t_shell *sh);

//exit.c
int		ft_is_numeric(char **cmd);
void	ft_free_exit(t_shell *sh);
void	exec_exit(t_shell *sh, t_cmd *cmds);

//cli.c
void	ft_eof_close(t_shell *sh);
void	reset_cli(t_shell *sh);
int		start_cli(t_shell *sh);

//env_utils.c
char	*ft_get_env(char *var_name, char **env);
void	ft_change_var(char *var_name, char *content, char **env);
char	**clone_envp(t_shell *sh, char **envp);
int		ft_strcmp_var(char *env_var, char *new_var);
int		ft_find_var(char *new_var, char **envp);

//print_env.c
void	ft_print_env(t_shell *sh);

//cmds.c
void	ft_cmd_addback(t_cmd **cmd, t_cmd *new_cmd);
char	**append_cmd(char **cmd, char *newcmd);
t_cmd	*cmd_init(bool from_pipe);
int		extract_cmd(t_cmd **cmd, t_token **token, bool from_pipe, t_shell *sh);
int		create_cmds(t_shell *sh);

//cmd_utils.c
int		perm_error(t_cmd *cmd);
void	get_pids(t_shell *sh, t_cmd *cmd);
void	ft_free_until_cmds(t_shell *sh);
void	free_all_cmds(t_shell *sh, t_cmd *current);
void	free_single_cmd(t_cmd *cmd);

//exec_builtin.c
void	free_builtin(t_cmd *cmd, t_shell *sh);
void	exec_builtin(t_cmd *cmd, t_shell *sh);
int		ft_is_builtin(char **cmds);

//exec_cmd.c
void	ft_execve_error(t_shell *sh, char *path);
void	exec_cmd(t_cmd *cmds, char **env, t_shell *sh);
void	close_cmd_fds(t_cmd *cmd);

//exec_erros.c
void	ft_path_error(t_shell *sh, t_cmd *cmds);
int		ft_isrelative(char *str);
void	ft_command_error(t_cmd *cmd, char *path, char **cmds, t_shell *sh);
void	handle_perm_error(t_cmd *cmd, t_shell *sh);
void	close_pipes(t_shell *sh, t_cmd *cmd);

//execute.c
void	execute(t_shell *sh);

//execute_utils.c
int		get_fdout(t_cmd *cmd, t_shell *sh);
int		get_fdin(t_cmd *cmd, t_shell *sh);
int		create_pipe(t_shell *sh, t_cmd *cmd);
int		fork_cmd(t_cmd *cmd, int *pid);
void	change_pipes(t_shell *sh, t_cmd *cmd);

//execute_pipes_utils.c
void	ft_close_execute_pipes(t_cmd *cmd);
int		init_exec_commands(t_shell *sh, t_cmd *cmd, int *pid);

//get_fds.c
t_token	*getfd_tofile(t_token *token, t_cmd *newcmd);
t_token	*getfd_infile(t_token *token, t_cmd *newcmd);
t_token	*getfd_append(t_token *token, t_cmd *newcmd);
t_token	*getfd_heredoc(t_token *token, t_cmd *newcmd, t_shell *sh);
t_token	*get_command(t_token *token, t_cmd *newcmd);

//path_finder.c
int		is_character_device(const char *path);
int		is_folder(char *path);
int		is_file(char *path);
char	*path_finder(char *cmds, char **env);
char	*local_path_finder(char *cmd, bool from_path_finder);

//free_array.c
void	ft_free(char **str);

//free_child.c
void	ft_free_child_pipes(t_shell *sh);

//free_cmds.c
void	free_cmds(t_shell *sh);

//free_heredoc.c
void	free_pipes(t_shell *sh);
void	handle_exit(t_shell *sh);
void	free_exit(t_shell *sh, char *end, int heredoc_i, char *prompt);

//wild_card_bonus.c
int		ft_match(char *str, char *line);
char	*get_dir(DIR *directory);
char	*get_arg(DIR *directory, char *str);
int		has_wildcard(char *str);

//free_tokens.c
void	free_tokens(t_token	*token);
void	ft_free_tokenize(t_token *token, char *prompt);

//expand.c
void	set_quotes(char c, bool *in_single_quotes, bool *in_quotes);
char	*expand(char *str, t_shell *sh, bool heredoc, size_t i);
void	expand_tokens(t_shell *sh);

//expand_utils.c
char	*extract_variable(char *str, int i);
int		ft_is_all_var(char	*str);
char	*ft_expand_string(char *str, size_t *i, t_shell *sh);
char	*ft_expand_exit(char *str, size_t *i);
char	*ft_expand_vars(char *str, size_t *i, t_shell *sh);

//heredoc.c
void	handle_heredoc_child(t_shell *sh, t_token *token, int heredoc_i);
int		handle_heredoc_parent(t_shell *sh, int pid);
int		get_heredoc(t_shell *sh);
void	start_heredoc(t_shell *sh, int heredoc_i);
void	ft_get_heredoc(t_shell *sh, char *end, int heredoc_i, bool quote);

//heredoc_utils.c
int		here_doc_loop(t_token *token, t_shell *sh, int *heredoc_i, int *pid);
int		has_quotes(char *str);
int		ft_heredoc_init(t_shell *sh);
int		not_prompt(t_shell *sh, char *end, int heredoc_i, char *prompt);

//string_utils.c
char	ft_ischar(int *i);
char	*remove_quotes(char *str);
char	*ft_insertstr(char	*string, size_t index, char *substr);
int		check_quotes(char *prompt);
int		has_equals(char *str);

//syntax_check.c
int		check_tokens(t_token *token);
int		check_syntax(t_shell *sh);

//tokenize.c
int		tokenize(char *prompt, t_shell *sh);

//token_utils.c
t_token	*ft_tokennew(char *str, int type);
void	ft_token_addback(t_token **token, t_token *new_token);
int		is_operator(char prompt);
int		is_space(char prompt);
int		is_var(char *token);

//token_last.c
int		ft_type(t_token *tokens);
int		is_redir(char c);

//exit_status.c
int		ft_exit(int exit_code, bool set, bool close);

//signal_handler.c
void	signal_handler(int sig);
void	ft_heredoc_child_signal_handler(int sig);
void	ft_heredoc_parent_signal_handler(int sig);
void	child_signal_handler(int sig);
void	signal_reset(void);

//error messages
# define HOME_ERROR	"minishell: cd: HOME not set\n"
# define UNEXPECTED_T "minishell: syntax error: unexpected token"
# define REDIRECT_T "minishell: Expected argument after"
# define INVALID_I "not a valid identifier"
# define LONGMAX 9223372036854775807
# define LONGMIN -9223372036854775808

#endif
