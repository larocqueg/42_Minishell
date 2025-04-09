/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:48:54 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/07 20:53:25 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmds(t_shell *sh)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	cmd = sh->cmd;
	temp = cmd;
	while (cmd)
	{
		temp = cmd -> next;
		ft_free(cmd->cmd);
		free(cmd);
		cmd = temp;
	}
}
