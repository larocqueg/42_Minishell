/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:07:17 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/22 18:26:16 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	ft_close_execute_pipes(t_cmd *cmd)
{
	if (cmd->to_pipe || cmd->from_pipe || !ft_is_builtin(cmd->cmd))
	{
		if (cmd->fd_in != -1 && !cmd->heredoc)
		{
			close(cmd->fd_in);
			cmd->fd_in = -1;
		}
		if (cmd->fd_out != -1)
		{
			close(cmd->fd_out);
			cmd->fd_in = -1;
		}
	}
}

int	init_exec_commands(t_shell *sh, t_cmd *cmd, int *pid)
{
	if (!create_pipe(sh, cmd))
	{
		if (cmd->from_pipe)
		{
			close(sh->pipe_old[0]);
			free(sh->pipe_old);
		}
		return (0);
	}
	if (!fork_cmd(cmd, pid))
	{
		if (cmd->from_pipe)
		{
			close(sh->pipe_old[0]);
			free(sh->pipe_old);
		}
		if (cmd->to_pipe)
		{
			close(sh->pipe_new[1]);
			close(sh->pipe_new[0]);
			free(sh->pipe_new);
		}
		return (0);
	}
	return (1);
}
