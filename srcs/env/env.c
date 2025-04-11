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

void	ft_print_env(t_shell *sh)
{
	int		i;
	char	**temp;

	i = 0;
	temp = sh->envp;
	while (temp[i])
		ft_printf("%s\n", temp[i++]);
}
