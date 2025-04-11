/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:47:15 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/11 19:06:25 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_command_error(char **cmds, char *path, int *exit_code)
{
	if (path && ((access(path, F_OK) == 0 && access(path, X_OK) != 0)
			|| is_character_device(path)))
	{
		ft_putstr_fd("minishell: permission denied: \"", 2);
		*exit_code = 126;
	}
	else if (!is_folder(path) && !is_file(path) && (ft_strncmp("./", cmds[0], 2) == 0 || ft_strncmp("/", cmds[0], 1) == 0))
		ft_putstr_fd("minishell: no such file or directory \"", 2);
	else if (is_folder(path) &&  (ft_strncmp("./", cmds[0], 2) == 0
		|| ft_strncmp("/", cmds[0], 1) == 0))
	{
		ft_putstr_fd("minishell: prompt is a directory! \"", 2);
		*exit_code = 126;
	}
	else
	{
		ft_putstr_fd("minishell: command not found \"", 2);
	}
	if (cmds[0])
		ft_putstr_fd(cmds[0], 2);
	ft_putstr_fd("\"\n", 2);
	if (path)
		free(path);
}

void	executecmd(t_cmd *cmds, char **env, t_shell *sh)
{
	char	*path;
	int		exit_code;

	exit_code = 127;
	close(sh->original_stdin);
	close(sh->original_stdout);
	if (!cmds->cmd || !*cmds->cmd)
	{
		free_cmds(sh);
		free_envp(sh);
		ft_exit_status(0, 1, 1);
	}
	path = NULL;
	if (ft_strncmp("./", cmds->cmd[0], 2) == 0 || ft_strncmp("/", cmds->cmd[0], 1) == 0)
		path = local_path_finder(cmds->cmd[0]);
	else if (cmds->cmd[0] && !is_folder(cmds->cmd[0]))
		path = path_finder(cmds->cmd[0], env);
	else
		path = cmds->cmd[0];
	if (!path || access(path, X_OK) != 0 || is_folder(path) || is_character_device(path))
	{
		ft_command_error(cmds->cmd, path, &exit_code);
		free_envp(sh);
		if (cmds->to_pipe)
			free(sh->pipe_new);
		if (cmds->from_pipe)
			free(sh->pipe_old);
		free_cmds(sh);
		exit(exit_code);
	}
	execve(path, cmds->cmd, env);
	ft_fprintf(2, "cannot execute '%s'\n", path);
	free_cmds(sh);
	free_envp(sh);
	free(path);
	ft_exit_status(8, 1, 1);
}

int	get_fdout(t_cmd *cmd, t_shell *sh)
{
	int outfd;

	outfd = STDOUT_FILENO;
	if (cmd -> to_pipe && cmd ->fd_out == -1)
	{
		close(sh->pipe_new[0]);
		outfd = sh->pipe_new[1];
	}
	else if (cmd -> fd_out != -1 )
	{
		if (cmd->to_pipe)
		{
			close(sh->pipe_new[0]);
			close(sh->pipe_new[1]);
		}
		outfd = cmd -> fd_out;
	}
	return (outfd);
}

int	get_fdin(t_cmd *cmd, t_shell *sh)
{
	int fdin = STDIN_FILENO;

	if (cmd -> from_pipe && fdin != -1)
	{
		fdin = sh->pipe_old[0];
	}
	if (cmd -> fd_in != -1)
	{
		if (cmd->from_pipe)
			close(sh->pipe_old[0]);
		fdin = cmd -> fd_in;
	}
	return (fdin);
}

void	handle_perm_error(t_cmd *cmd)
{
	ft_fprintf(2, "minishell: Permission denied or file does not exist!\n");
	if ((cmd->to_pipe || cmd->from_pipe) && !cmd->cmd && cmd->infile_error)
		ft_exit_status(0, true, true);
	ft_exit_status(1, true, false);
	if (cmd->to_pipe || cmd->from_pipe || !ft_is_builtin(cmd->cmd))
		ft_exit_status(0, 0, 1);
}
void	handle_child(t_shell *sh, t_cmd *cmd)
{
	int outfd;
	int infd;

	outfd = get_fdout(cmd, sh);
	infd = get_fdin(cmd, sh);
	if (outfd != STDOUT_FILENO)
	{
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
	}
	if (infd != STDIN_FILENO)
	{
		dup2(infd, STDIN_FILENO);
		close(infd);
	}
	if (!perm_error(cmd) && ft_is_builtin(cmd->cmd))
		execute_builtin(cmd, sh);
	else if (!perm_error(cmd))
		executecmd(cmd, sh->envp, sh);
	if (perm_error(cmd))
		handle_perm_error(cmd);
	close(outfd);
	close(infd);
}

static void	exec_cmd(t_shell *sh, t_cmd *cmd)
{
	int		pid;
	int		pid_count;
	t_cmd	*tmp;
	int		status;

	pid_count = 0;
	pid = -1;
	status = 0;
	tmp = cmd;
	while (tmp)
	{
		pid_count++;
		tmp = tmp->next;
	}
	while (cmd)
	{
		if (cmd->to_pipe)
		{
			sh->pipe_new = malloc(sizeof(int) * 2);
			pipe(sh->pipe_new);		}
		if (cmd->from_pipe || !ft_is_builtin(cmd->cmd) || cmd->to_pipe)
		{
			if (sh->DEBUG)
				printf("forked!!!!\n");
			pid = fork();
		}
		else
			pid = -1;
		if (pid == 0 || pid == -1)
		{
			signal_default();
			handle_child(sh, cmd);
		}
		if (cmd->from_pipe)
		{
			close(sh->pipe_old[0]);
			free(sh->pipe_old);
			sh->pipe_old = NULL;
		}
		if (cmd->to_pipe)
		{
			close(sh->pipe_new[1]);
			sh->pipe_old = sh->pipe_new;
			sh->pipe_new = NULL;
		}
		cmd = cmd->next;
	}
	if (pid != 0 && pid != -1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
	}
	if (WIFEXITED(status))
	{
		ft_exit_status(WEXITSTATUS(status), true, false);
	}
	else if (WIFSIGNALED(status))
	{
		ft_exit_status(WTERMSIG(status) + 128, true, false);
	}
	if (ft_exit_status(0, 0, 0) == 131)
		ft_fprintf(2, "Quit (core dumped)\n");
}

void execute(t_shell *sh)
{
	t_cmd *cmd;

	cmd = sh->cmd;
	free_tokens(sh->token);
	exec_cmd(sh, cmd);
	free_cmds(sh);
	free_pipes(sh);
}
