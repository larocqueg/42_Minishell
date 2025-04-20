/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:05:10 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/20 18:05:11 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	exec_env(t_shell *sh, t_cmd *cmd)
{
	if (get_argc(cmd->cmd) > 1)
	{
		ft_fprintf(2, "env: too many arguments\n");
		ft_exit(1, 1, 0);
		return ;
	}
	else
	{
		ft_print_env(sh);
		ft_exit(0, 1, 0);
	}
}
