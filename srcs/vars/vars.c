/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:43:52 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 18:48:39 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
static int	get_local_len(char **var)
{
	int	i;

	if (!var || !*var)
		return (0);
	i = 0;
	while (var[i])
		i++;
	return (i);
}

static void	clone_vars(t_shell *sh, char *new_var)
{
	int	i;
	char	**local_temp;

	sh->local_vars = malloc(sizeof(char *) * (get_local_len(sh->local_vars) + 2));
	sh->local_vars[i++] = ft_strdup(new_var);
	sh->local_vars[i] = NULL;
}*/
/*
static void	free_local(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->local_vars[i])
		free(sh->local_vars[i++]);
	free(sh->local_vars);
}*/

void	handle_vars(t_shell *sh, char *var)
{
	char	*var_name;
	char	*no_equals;
	char	*content;
	char	*expanded_var;

	content = ft_strdup(var + ft_strlen_tochar(var, '=') + 1);
	var_name = ft_strndupmod(var, 0, ft_strlen_tochar(var, '='));
	no_equals = ft_strndupmod(var, 0, ft_strlen_tochar(var, '=') - 1);
	expanded_var = expand(var, false, false, sh, false);
	if (!ft_get_env(no_equals, sh->envp))
	{
		if (ft_get_env(no_equals, sh->local_vars)
				|| (sh->local_vars && ft_find_var(no_equals, sh->local_vars)))
			ft_change_var(var_name, expanded_var + ft_strlen_tochar(var, '=') + 1, sh->local_vars);
		else
		{
			sh->local_vars = append_cmd(sh->local_vars, expanded_var);
			free(var_name);
			free(no_equals);
		}
		return ;
	}
	else
	{
		ft_change_var(var_name, expanded_var + ft_strlen_tochar(var, '=') + 1, sh->envp);
	}
}
