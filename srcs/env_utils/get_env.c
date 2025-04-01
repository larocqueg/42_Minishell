/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:26:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/01 20:06:42 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_env(char *var_name, t_shell *sh)
{
	int		i;
//	char	*env_result;
	char	**env;

	env= sh->envp;

	i = 0;
	while(env[i])
	{
		if (ft_strcmp_tochar(var_name, env[i], '=') == -61)
		{
			return (env[i] + ft_strlen_tochar(env[i], '=' ));
		}
		i++;
	}
	return (NULL);
}
