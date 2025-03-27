/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:47:15 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/27 21:58:52 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

# define INFILE_ERROR "Error: No such file or directory \"infile\"\n"
# define OUTFILE_ERROR "Error: No such file or directory \"outfile\"\n"
# define AV_ERROR_1		"Error: Bad arguments!\n"
# define AV_ERROR_2	"Usage: $> ./pipex \"file1\" \"cmd1\" \"cmd2\" \"file2\"\n"
# define PID_ERROR	"Error while trying to create a fork!\n"
# define PIPE_ERROR	"Error while trying to create a pipe!\n"
# define PATH_ERROR	"Error: PATH not found!\n"

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

void	ft_command_error(char **cmds)
{
	ft_putstr_fd("Error: command not found \"", 2);
	if (cmds[0])
		ft_putstr_fd(cmds[0], 2);
	ft_putstr_fd("\"\n", 2);
	ft_free(cmds);
}

char	*path_finder(char *cmds, char **env)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (!env[i])
		ft_error(PATH_ERROR);
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmds);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	ft_free(paths);
	return (0);
}

void	executecmd(char **cmds, char **env)
{
	int		x;
	char	*path;

	path = path_finder(cmds[0], env);
	if (!path)
	{
		ft_command_error(cmds);
		ft_error(NULL);
		exit(127);
	}
	x = execve(path, cmds, env);
	exit_code = x;
	if (x == -1)
		ft_error(NULL);
}

int	get_fdout(t_cmd *cmd, t_shell *sh)
{
	int outfd;

	outfd = 1;
	//close(sh->pipe_new[0]);
	if (cmd -> to_pipe && cmd ->fd_out == -1)
	{
		outfd = sh->pipe_new[1];
	}
	else if (cmd -> fd_out != -1)
	{
		close (sh->pipe_new[1]);
		outfd = cmd -> fd_out;
	}
	return (outfd);
}

int	get_fdin(t_cmd *cmd, t_shell *sh)
{
	int fdin = 0;

	//close(sh->pipe_old[1]);
	if (cmd -> from_pipe)
	{
		fdin = sh->pipe_old[0];
	}
	if (cmd -> fd_in != -1)
	{
		fdin = cmd -> fd_in;
	}
	return(fdin);
}

void	handle_child(t_shell *sh, t_cmd *cmd)
{
	int pid;
	int outfd;
	int infd;

	outfd = get_fdout(cmd, sh);
	infd = get_fdin(cmd, sh);
	dup2(outfd, STDOUT_FILENO);
	dup2(infd, STDIN_FILENO);

	executecmd(cmd->cmd, sh->envp);
	close(outfd);
	close(infd);
}

void	handle_parent(t_shell *sh, t_cmd *cmd)
{
	int outfd;
	int infd;

	outfd = get_fdout(cmd, sh);
	infd = get_fdin(cmd, sh);

	dup2(outfd, STDOUT_FILENO);
	dup2(infd, STDIN_FILENO);
	executecmd(cmd->cmd, sh->envp);
	close(outfd);
	close(infd);
}
void	exec_cmd(t_shell *sh, t_cmd *cmd)
{
	int pid;
	while (cmd)
	{
		if (cmd -> from_pipe)
		{
		if (sh->pipe_old)
			free(sh->pipe_old);
		sh->pipe_old = sh->pipe_new;
		close(sh->pipe_old[1]);
		}
		if ((cmd) -> to_pipe)
		{
			sh -> pipe_new = malloc(sizeof(int) * 2);
			pipe(sh -> pipe_new);
			pid = fork();
			if (pid != 0)
				wait(NULL);
			else
				handle_child(sh, (cmd));
		}
		else
			handle_parent(sh, (cmd));
		(cmd) = (cmd)->next;
	}
}
void execute(t_shell *sh)
{
	t_cmd *cmd;
	cmd = sh->cmd;
	exec_cmd(sh, cmd); // Execute the commands

}
// void	execute(t_shell *sh)
// {
// 	t_cmd *cmd;
// 	int		pid;

// 	cmd = sh->cmd;
// 	exec_cmd(sh, cmd);
// }
