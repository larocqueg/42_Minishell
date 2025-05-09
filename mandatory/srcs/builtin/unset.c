/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:52:17 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/05/01 21:24:51 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_free_back(char **new_env, int k)
{
	while (k >= 0)
		free(new_env[k--]);
	free(new_env);
	return (NULL);
}

int	ft_strcmp_unset(char *env, char *cmd)
{
	int	i;

	i = 0;
	if (env && *env)
	{
		while ((env[i] && cmd[i]) && env[i] == cmd[i])
		{
			i++;
		}
		if ((!env[i] || env[i] == '=') && cmd[i] == '\0')
			return (1);
		return (0);
	}
	return (0);
}

static int	ft_count_vars(t_shell *sh, char **cmd)
{
	int	i;
	int	j;
	int	count;

	j = 1;
	count = 0;
	sh->old_env_size = sh->env_size;
	while (cmd[j])
	{
		i = 0;
		while (sh->envp[i])
		{
			if (ft_strcmp_unset(sh->envp[i], cmd[j]))
			{
				count++;
				break ;
			}
			i++;
		}
		j++;
	}
	return (count);
}

char	**ft_get_unset(t_shell *sh, char **new_env, char **cmd, int k)
{
	int	i;
	int	j;

	i = 0;
	new_env = malloc(sizeof(char *) * (sh->env_size + 1));
	if (!new_env)
		return (NULL);
	while (i < sh->old_env_size)
	{
		j = 1;
		while (cmd[j])
		{
			if (*sh->envp && ft_strcmp_unset(sh->envp[i], cmd[j]))
				i++;
			j++;
		}
		if (i < sh->old_env_size)
			new_env[k++] = ft_strdup(sh->envp[i]);
		i++;
		if (k > 0 && !new_env[k - 1])
			return (ft_free_back(new_env, k - 2));
	}
	new_env[sh->env_size] = NULL;
	return (new_env);
}

void	exec_unset(t_shell *sh, char **cmd)
{
	int		count;
	char	**new_env;

	if (sh->env_size == 0)
	{
		ft_exit(0, true, false);
		return ;
	}
	new_env = NULL;
	count = ft_count_vars(sh, cmd);
	if (count == 0)
	{
		ft_exit(0, true, false);
		return ;
	}
	sh->env_size = sh->env_size - count;
	new_env = ft_get_unset(sh, new_env, cmd, 0);
	if (!new_env)
		return ;
	ft_free(sh->envp);
	sh->envp = new_env;
	ft_exit(0, 1, 0);
}
