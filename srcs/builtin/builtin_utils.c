/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:01:04 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/01 19:01:17 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_swap(char **s1, char **s2)
{
	char *temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

int	ft_strcmp_tochar(const char *s1, const char *s2, char c)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) || s1[i] != c || s2[i] != c)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	**clone_envp(char **envp)
{
	int	i;
	char **dest;

	i = 0;
	while (envp[i])
		i++;
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		dest[i] = ft_strdup(envp[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

void	free_envp(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->envp[i])
		free(sh->envp[i++]);
	free(sh->envp);
}
