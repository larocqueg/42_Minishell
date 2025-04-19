/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:16:32 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/19 11:33:21 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_pwd(t_cmd *cmd)
{
	char	**cmds;
	char	*current_pwd;

	cmds = cmd->cmd;
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		ft_fprintf(2, "pwd: error retrieving current directory!\n");
		ft_exit(1, 1, 0);
	}
	else
	{
		ft_printf("%s\n", current_pwd);
		free(current_pwd);
		ft_exit(0, 1, 0);
	}
}
