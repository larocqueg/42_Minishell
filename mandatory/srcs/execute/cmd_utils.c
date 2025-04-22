/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:52:22 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/22 19:33:50 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	perm_error(t_cmd *cmd)
{
	if (cmd->infile_error || cmd->tofile_error)
		return (1);
	else
		return (0);
}

void	ft_free_until_cmds(t_shell *sh)
{
	free_tokens(sh->token);
	free_cmds(sh);
}

void	get_pids(t_shell *sh, t_cmd *cmd)
{
	int		count;
	t_cmd	*temp;

	temp = cmd;
	count = 0;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	if (count > 0)
		sh->pids = malloc(sizeof(int) * count);
}

void	free_all_cmds(t_shell *sh, t_cmd *current)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	if (sh->pids != NULL)
		free(sh->pids);
	sh->pids = NULL;
	if (!sh->cmd || ((!current->from_pipe && !current->to_pipe)
			&& ft_is_builtin(current->cmd)))
		return ;
	cmd = sh->cmd;
	temp = cmd;
	while (cmd)
	{
		temp = cmd -> next;
		if (cmd == current)
		{
			cmd = temp;
			continue ;
		}
		ft_free(cmd->cmd);
		close_cmd_fds(cmd);
		free(cmd);
		cmd = temp;
	}
}

void	free_single_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
		ft_free(cmd->cmd);
	free(cmd);
}
