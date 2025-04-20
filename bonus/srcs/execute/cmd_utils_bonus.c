/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:46:16 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/20 18:46:17 by gde-la-r         ###   ########.fr       */
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
