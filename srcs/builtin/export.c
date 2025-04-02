/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:00:07 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/02 18:47:42 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	put_export(char *str)
{
	int		i;
	bool	equal;

	equal = false;
	i = 0;
	ft_printf("declare -x ");
	while(str[i])
	{
		if (str[i] == '=' && !equal)
		{
			equal = true;
			write(1, &str[i++], 1);
			write(1, "\"", 1);
		}
		else
			write(1, &str[i++], 1);
	}
	write(1, "\"\n", 2);
}

void	print_export(t_shell *sh)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	temp = clone_envp(sh->envp);
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
	i = 0;
	while (temp[i])
	{
		put_export(temp[i]);
		free(temp[i++]);
	}
	free(temp);
	return ;
}
