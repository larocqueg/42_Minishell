/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:54:59 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/19 17:15:28 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_cd(char **cmd)
{
	if (cmd[1] == NULL)
	{
		chdir(getenv("HOME"));
		return 1;
	}
	if (chdir(cmd[1]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
		return 1;
	}
	return 1;
}

int	check_cmd(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return 1;
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return(exec_cd(cmd));
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return 1;
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return 1;
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return 1;
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		return 1;
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return 1;
	return 0;
}
