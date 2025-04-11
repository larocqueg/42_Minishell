/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 20:23:18 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/11 21:01:50 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_fdout(t_cmd *cmd, t_shell *sh)
{
	int	outfd;

	outfd = STDOUT_FILENO;
	if (cmd -> to_pipe && cmd ->fd_out == -1)
	{
		close(sh->pipe_new[0]);
		outfd = sh->pipe_new[1];
	}
	else if (cmd -> fd_out != -1)
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
	int	fdin;

	fdin = STDIN_FILENO;
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

int	create_pipe(t_shell *sh, t_cmd *cmd)
{
	if (cmd->to_pipe)
	{
		sh->pipe_new = malloc(sizeof(int) * 2);
		if (!sh->pipe_new)
			return (0);
		pipe(sh->pipe_new);
		if (!sh->pipe_new)
		{
			free(sh->pipe_new);
			return (0);
		}
	}
	return (1);
}

int	fork_cmd(t_shell *sh, t_cmd *cmd, int *pid)
{
	if (cmd->from_pipe || !ft_is_builtin(cmd->cmd) || cmd->to_pipe)
	{
		*pid = fork();
		if (*pid == -1)
			return (0);
	}
	return (1);
}

void	change_pipes(t_shell *sh, t_cmd *cmd)
{
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
}
