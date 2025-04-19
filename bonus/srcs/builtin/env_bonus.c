/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:14:30 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/13 21:19:31 by rafaelfe         ###   ########.fr       */
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
