/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:00:07 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/01 19:00:57 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(t_shell *sh)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	temp2 = clone_envp(sh->envp);
	while (temp[i])
	{
		j = i + 1;
		while (temp[j])
		{
			if (ft_strcmp_tochar(temp[i], temp[j], '=') > 0 )
				ft_swap(&temp[i], &temp[j]);
			j++;
		}
		i++;
	}
	if (sh->DEBUG)
	{
		i = 0;
		while (temp[i])
		{
			printf("%s\n", temp[i]);
			free(temp[i++]);
		}
		free(temp);
	}
	else
	{
		i = 0;
		while (temp[i])
		{
			printf("%s\n", temp[i]);
			free(temp[i++]);
		}
		free(temp);
		return ;
	}
}
