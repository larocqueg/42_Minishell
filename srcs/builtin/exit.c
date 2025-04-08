/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:28:58 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/08 19:18:02 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_exit(t_shell *sh, t_cmd *cmds)
{
	if (cmds->cmd[1] == NULL)
	{
		//free cli_text ???
		free_envp(sh);
		free_cmds(sh);
		ft_printf("exit\n");
		ft_exit_status(0, 0, 1);
	}
}
