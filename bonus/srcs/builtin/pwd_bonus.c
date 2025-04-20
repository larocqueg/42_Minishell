/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:05:32 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/20 18:05:33 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	exec_pwd(t_cmd *cmd)
{
	char	*current_pwd;

	(void)cmd;
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
