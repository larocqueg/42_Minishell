/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:47:15 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/03 22:19:21 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *str)
{
	if (str != NULL)
		ft_putstr_fd(str, 2);
	return ;
}

void	ft_free(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int is_folder(char *path)
{
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISDIR(path_stat.st_mode);
}

int is_file(char *path)
{
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISREG(path_stat.st_mode);
}

void	ft_command_error(char **cmds, char *path, int *exit_code)
{
	if (!is_folder(path) && !is_file(path))
		ft_putstr_fd("minishell: no such file or directory \"", 2);
	else if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: cannot execute command \"", 2);
		*exit_code = 126;
	}
	else if (is_folder(path))
	{
		ft_putstr_fd("minishell: prompt is a directory! \"", 2);
		*exit_code = 126;
	}
	else
		ft_putstr_fd("minishell: command not found \"", 2);
	if (cmds[0])
		ft_putstr_fd(cmds[0], 2);
	ft_putstr_fd("\"\n", 2);
	ft_free(cmds);
}

char	*path_finder(char *cmds, char **env)
{
	int		i;
	char	**paths;
	char	*part_path;
	char	*path;

	path = ft_get_env("PATH", env);
	if (!path)
		ft_error(PATH_ERROR);
	paths = ft_split(path + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmds);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);

		i++;
	}
	free(path);
	ft_free(paths);
	return (0);
}


/*char	*path_finder(char *cmds, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmds);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path); // clone path and them free all?

		i++;
	}
	free(path);
	ft_free(paths);
	return (0);
}*/
char	*local_path_finder(char *cmd)
{
	char	*path;
	char	*temp;
	bool	is_relative;

	is_relative = false;
	if (ft_strncmp("./", cmd, 2) == 0)
	{
		is_relative= true;
		path = getcwd(NULL, 0);
		temp = ft_strjoin(path, "/");
		free(path);
		path = ft_strjoin(temp, cmd + 2);
	}
	else
		path = cmd;
	if (access(path, F_OK) == 0 && (is_file(path) || is_folder(path)))
		return (path);
	if (is_relative)
		free(path);
	return (NULL);
}

void	executecmd(char **cmds, char **env)
{
	int		x;
	char	*path;
	int		exit_code = 127;

	path = NULL;

	if (ft_strncmp("./", cmds[0], 2) == 0 || ft_strncmp("/", cmds[0], 1) == 0)
		path = local_path_finder(cmds[0]);
	else if (!is_folder(cmds[0]))
		path = path_finder(cmds[0], env);
	else
		path = cmds[0];
			if (!path || access(path, X_OK) != 0 || is_folder(path))
	{
		ft_command_error(cmds, path, &exit_code);
		ft_error(NULL);
		exit(exit_code);
	}
	x = execve(path, cmds, env);
	if (x == -1)
		ft_error(NULL);
}

void 	execute_builtin(t_cmd *cmd, t_shell *sh)
{
	int	i;

	if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
	{
		printf("exit\n");
		free_envp(sh);
		exit(0);
	}
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
	{
		exec_cd(cmd->cmd, sh);
	}
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
	{
		exec_export(sh, cmd);
	}
	else if (is_var(cmd->cmd[0]) || ft_strncmp(cmd->cmd[0], "env", 4) == 0)
	{
		i = 0;
		if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		{
			i = 0;
			while (sh->envp[i])
			{
				if (is_var(sh->envp[i]))
					printf("%s\n", sh->envp[i]);
				i++;
			}
		}
		else
		{
			while (cmd->cmd[i])
				handle_vars(sh, cmd->cmd[i++]);
			if (!sh->DEBUG)
				return;
			i = 0;
			while (sh->local_vars[i])
				printf("%s\n", sh->local_vars[i++]);
		}
	}
	if (cmd->to_pipe || cmd->from_pipe)
		exit(sh->exit_code);
}


int	ft_is_builtin(char **cmds)
{
	if (ft_strncmp(cmds[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmds[0], "print", 6) == 0)
		return (1);
	else if (ft_strncmp(cmds[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmds[0], "cd", 3) == 0)
		return (1);
	else if (is_var(cmds[0]))
		return (1);
	else if (ft_strncmp(cmds[0], "env", 4) == 0)
		return (1);
	return (0);
}

int	get_fdout(t_cmd *cmd, t_shell *sh)
{
	int outfd;

	outfd = 1;
	if (cmd -> to_pipe && cmd ->fd_out == -1)
	{
		outfd = sh->pipe_new[1];
	}
	else if (cmd -> fd_out != -1)
	{
		outfd = cmd -> fd_out;
	}
	return (outfd);
}

int	get_fdin(t_cmd *cmd, t_shell *sh)
{
	int fdin = 0;

	if (cmd -> from_pipe && fdin != -1)
	{
		fdin = sh->pipe_old[0];
	}
	if (cmd -> fd_in != -1)
	{
		fdin = cmd -> fd_in;
	}
	return (fdin);
}

void	handle_child(t_shell *sh, t_cmd *cmd)
{
	int outfd;
	int infd;

	if (sh->DEBUG)
		printf("---------------executing child!-------------\n");
	outfd = get_fdout(cmd, sh);
	infd = get_fdin(cmd, sh);
	dup2(outfd, STDOUT_FILENO);
	dup2(infd, STDIN_FILENO);
	if (cmd -> fd_out != -1)
		close (cmd->fd_out);
	if (cmd -> fd_in != -1)
		close(cmd ->fd_in);
	if (!cmd->perm_error && ft_is_builtin(cmd->cmd))
		execute_builtin(cmd, sh);
	else if (!cmd->perm_error)
		executecmd(cmd->cmd, sh->envp );
	if (cmd->perm_error)
	{
		write(2, "minishell: file: Permission denied!\n", 36);
		if (cmd->to_pipe || cmd->from_pipe || !ft_is_builtin(cmd->cmd))
			exit(1);
		sh->exit_code = 1;
	}
	close(outfd);
	close(infd);
}


/*
void	exec_cmd(t_shell *sh, t_cmd *cmd)
{
	int pid;

	pid = 0;
	while (cmd)
	{
		if (cmd -> from_pipe)
		{
			if (sh->pipe_old)
			{
				close(sh->pipe_old[0]);
				free(sh->pipe_old);
				sh->pipe_old = NULL;
			}
			sh->pipe_old = sh->pipe_new;
			close(sh->pipe_old[1]);
		}
		if ((cmd) -> to_pipe)
		{
			sh -> pipe_new = malloc(sizeof(int) * 2);
			pipe(sh -> pipe_new);

			pid = fork();
			if (pid != 0)
			{
				waitpid(pid, NULL, 0);
				if (sh->DEBUG)
					printf("---------end child!-------------\n");
			}
			else
				handle_child(sh, (cmd));
		}
		else
		{
			if (cmd->from_pipe || !ft_is_builtin(cmd->cmd)) // if not export, exit and unset and myvar FORK
				pid = fork();
			if (pid != 0)
			{
				waitpid(pid, NULL, 0);
				if (sh->DEBUG)
					printf("---------end parent!-------------\n");
			}
			else if (pid == 0)
				handle_parent(sh, (cmd));
		}
		(cmd) = (cmd)->next;
	}
}*/

static void	exec_cmd(t_shell *sh, t_cmd *cmd)
{
	int		*pids;
	int		i;
	int		pid_count;
	t_cmd	*tmp;
	int		status;

	pid_count = 0;
	tmp = cmd;
	while (tmp)
	{
		pid_count++;
		tmp = tmp->next;
	}
	pids = malloc(sizeof(int) * pid_count);
	if (!pids)
		return ;
	i = 0;
	while (cmd)
	{
		if (cmd->to_pipe)
		{
			sh->pipe_new = malloc(sizeof(int) * 2);
			pipe(sh->pipe_new);
		}
		if (cmd->from_pipe || !ft_is_builtin(cmd->cmd) || cmd->to_pipe)
		{
			if (sh->DEBUG)
				printf("forked!!!!\n");
			pids[i] = fork();
		}
		else
			pids[i] = 0;
		if (pids[i] == 0)
		{
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
			sh->pipe_old = sh->pipe_new;
			close(sh->pipe_old[1]);
		}
		cmd = cmd->next;
		i++;
	}
	i = 0;
	while (i < pid_count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
	{
		sh->exit_code = WEXITSTATUS(status);
	}
	else

	free(pids);
	t_cmd *temp = sh->cmd;
	while(temp)
	{
		tmp = temp;
		ft_free(tmp->cmd);
		temp = temp->next;
		free(tmp);
	}
}

void execute(t_shell *sh)
{
	t_cmd *cmd;
	cmd = sh->cmd;
	exec_cmd(sh, cmd);

}
