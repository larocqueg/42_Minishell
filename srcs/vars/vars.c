/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:43:52 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/02 12:45:15 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	clone_vars(t_shell *sh, char **old_env, char *new_var)
{
	int	i;

	i = 0;
	sh->env_size = 0;
	while (old_env[sh->env_size])
		sh->env_size++;
	sh->envp = malloc(sizeof(char *) * (sh->env_size + 2));
	while (old_env[i])
	{
		sh->envp[i] = ft_strdup(old_env[i]);
		i++;
	}
	sh->envp[i++] = ft_strdup(new_var);
	sh->envp[i] = NULL;
}

static void	create_vars(t_shell *sh, char *var)
{
	char **old_env;

	old_env = clone_envp(sh->envp);
	free_envp(sh);
	clone_vars(sh, old_env, var);
}

void	handle_vars(t_shell *sh, char *var)
{
	char	*var_name;
	char	*no_equals;
	//char	*expandedd_var;

	var_name = ft_strndupmod(var, 0, ft_strlen_tochar(var, '='));
	no_equals = ft_strndupmod(var, 0, ft_strlen_tochar(var, '=') - 1);
	if (!ft_get_env(no_equals, sh))
	{
		create_vars(sh, var);
		return ;
	}
	else
		ft_change_var(var_name, var + ft_strlen_tochar(var, '=') + 1, sh);
}
