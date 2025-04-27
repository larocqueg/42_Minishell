/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:05:48 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/27 20:09:05 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	get_new_env(t_shell *sh, int *i, int *k, char **new_env)
{
	if (*i == sh->env_size)
	{
		new_env[(*k)++] = ft_strdup(sh->envp[*i]);
		(*i)++;
	}
	else if (*i < sh->env_size)
		new_env[(*k)++] = ft_strdup(sh->envp[(*i)++]);
}
