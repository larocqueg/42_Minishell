/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:26:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/01 21:21:48 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_env(char *var_name, char **env)
{
	int		i;
//	char	*env_result;
	if (!env || !*env)
		return (NULL);
	i = 0;
	while(env[i])
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
	while(env[i])
	{
		if (ft_strncmp(var_name, env[i], 4) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin(var_name, content);
		}
		i++;
	}
}
