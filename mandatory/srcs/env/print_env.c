/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:12:08 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/11 17:13:35 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_valid_var_env(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		i++;
	}
	if (str[i] && str[i] == '=')
		return (1);
	else
		return (0);
}

void	ft_print_env(t_shell *sh)
{
	int		i;
	char	**temp;

	i = 0;
	temp = sh->envp;
	while (temp[i])
	{
		if (is_valid_var_env(temp[i]))
			ft_printf("%s\n", temp[i]);
		i++;
	}
}
