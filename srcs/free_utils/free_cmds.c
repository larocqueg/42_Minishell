/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:48:54 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/11 18:26:27 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmds(t_shell *sh)
{
	t_cmd	*cmd;
	t_cmd	*temp;
	int		pipe;

	pipe = false;
	cmd = sh->cmd;
	if (!cmd)
		return ;
	temp = cmd;
	while (cmd)
	{
		temp = cmd -> next;
		ft_free(cmd->cmd);
		if (cmd->to_pipe || cmd->from_pipe)
			pipe = true;
		if (pipe)
		{
			if (cmd->fd_out != -1)
				close(cmd->fd_out);
			if (cmd->fd_in != -1)
				close(cmd->fd_in);
		}
		free(cmd);
		cmd = temp;
	}
}
