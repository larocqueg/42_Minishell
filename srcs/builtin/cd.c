/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:13:00 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/01 19:21:59 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_cd(char **cmd, t_shell *sh)
{
	(void)sh;
	if (cmd[1] == NULL)
	{
		chdir(getenv("HOME")); // temos q fazer a get env!!!!!!!!!
		return (1);
	}
	if (chdir(cmd[1]) == -1)
	{
		printf("minihell: cd: %s: No such file or directory\n", cmd[1]);
		return (1);
	}
	return (1);
}
