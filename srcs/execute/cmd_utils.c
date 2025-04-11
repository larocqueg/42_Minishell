/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:52:22 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/11 18:07:59 by rafaelfe         ###   ########.fr       */
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

void	ft_freenaporratoda(void)
{
	return ;
}
