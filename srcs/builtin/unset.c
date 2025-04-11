/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:12:16 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/11 21:40:40 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_strcmp_unset(char *env, char *cmd)
{
	int	i;

	i = 0;
	while (env[i] == cmd[i])
	{
		i++;
	}
	if ((!env[i] || env[i] == '=') && cmd[i] == '\0')
		return (1);
	return (0);
}

static int	ft_count_vars(t_shell *sh, char **cmd)
{
	int	i;
	int	j;
	int	count;

	j = 1;
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

void	exec_unset(t_shell *sh, char **cmd)
{
	int		i;
	int		j;
	int		k;
	int		count;
	char	**new_env;

	count = ft_count_vars(sh, cmd);
	new_env = malloc(sizeof(char *) * (sh->env_size - count + 1));
	if (!new_env)
		return ;
	k = 0;
	i = 0;
	while (i < sh->env_size)
	{
		j = 1;
		while (cmd[j])
		{
			if (ft_strcmp_unset(sh->envp[i], cmd[j]))
			{
				i++;
				break ;
			}
			j++;
		}
		new_env[k++] = ft_strdup(sh->envp[i++]);
	}
	new_env[k] = NULL;
	ft_free(sh->envp);
	sh->envp = new_env;
	ft_exit_status(0, 1, 0);
}
