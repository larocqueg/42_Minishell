/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:26:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/13 21:46:07 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_env(char *var_name, char **env)
{
	int		i;

	if (!env || !*env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strcmp_tochar(var_name, env[i], '=') == -61)
		{
			return (env[i] + ft_strlen_tochar(env[i], '=' ) + 1);
		}
		i++;
	}
	return (NULL);
}

void	ft_change_var(char *var_name, char *content, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var_name, env[i], ft_strlen(var_name)) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin(var_name, content);
		}
		i++;
	}
}

char	**clone_envp(t_shell *sh, char **envp)
{
	int		i;
	char	**dest;

	i = 0;
	while (envp[i])
		i++;
	dest = malloc(sizeof(char **) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		dest[i] = ft_strdup(envp[i]);
		i++;
	}
	dest[i] = NULL;
	sh->env_size = i;
	return (dest);
}

int	ft_strcmp_var(char *env_var, char *new_var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env_var[i])
	{
		if (env_var[i] == new_var[i])
			i++;
		else if ((env_var[i] == '=' && !new_var[i])
			|| (!env_var[i] && !new_var[i]))
			return (1);
		else
			return (0);
	}
	return (0);
}

int	ft_find_var(char *new_var, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strcmp_var(envp[i], new_var))
			return (1);
		i++;
	}
	return (0);
}
