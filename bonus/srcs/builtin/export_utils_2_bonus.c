/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:05:56 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/20 18:05:58 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	ft_free_export(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		put_export(temp[i]);
		free(temp[i]);
		i++;
	}
}
