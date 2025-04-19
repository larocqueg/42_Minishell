/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:51:08 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/12 16:11:20 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	ft_free(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
