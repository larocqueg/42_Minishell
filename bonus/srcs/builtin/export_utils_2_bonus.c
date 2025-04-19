/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 00:37:27 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/18 00:40:00 by gde-la-r         ###   ########.fr       */
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
