/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:05:23 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/20 18:05:25 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	ft_is_flag(char *cmd)
{
	int	i;

	i = 1;
	if (!cmd)
		return (0);
	if (cmd[0] != '-')
		return (0);
	if (cmd[1] != 'n')
		return (0);
	while (cmd[i] == 'n')
	{
		i++;
	}
	if (cmd[i] != '\0')
		return (0);
	return (1);
}

void	exec_echo(t_cmd *cmds)
{
	char	**cmd;
	bool	flag;
	int		i;

	i = 1;
	flag = false;
	cmd = cmds->cmd;
	while (ft_is_flag(cmd[i]))
	{
		i++;
		flag = true;
	}
	while (cmd[i])
	{
		ft_printf("%s", cmd[i]);
		if (cmd[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!flag)
		ft_printf("\n");
	ft_exit(0, 1, 0);
}
