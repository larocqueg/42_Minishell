/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:05:48 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/27 20:43:23 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_new_env(t_shell *sh, int *i, int *k, char **new_env)
{
	if (*i < sh->old_env_size)
		new_env[(*k)++] = ft_strdup(sh->envp[(*i)]);
	(*i)++;
}
