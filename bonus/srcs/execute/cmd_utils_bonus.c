/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:52:22 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/11 21:49:20 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
