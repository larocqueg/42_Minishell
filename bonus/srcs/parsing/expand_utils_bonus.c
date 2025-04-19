/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:28:46 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/11 21:14:43 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

char	*extract_variable(char *str, int i)
{
	int	j;

	j = i;
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	if (j >= i)
		return (ft_strndupmod(str, i, --j));
	return (NULL);
}

int	ft_is_all_var(char	*str)
{
	int	i;

	i = 1;
	if (str[0] != '$')
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (!str[i])
		return (1);
	else
		return (0);
}

char	*ft_expand_string(char *str, size_t *i, t_shell *sh)
{
	char	*variable_name;
	char	*temp;
	char	*content;

	temp = NULL;
	variable_name = extract_variable(str, *i);
	if (!variable_name)
		return (free(str), NULL);
	content = ft_get_env(variable_name, sh->envp);
	free(variable_name);
	if (!content && ft_is_all_var(str))
		return (free(str), NULL);
	temp = ft_insertstr(str, (*i)--, content);
	free(str);
	str = temp;
	if (content)
	{
		(*i) += ft_strlen(content) - 1;
	}
	return (str);
}

char	*ft_expand_exit(char *str, size_t *i)
{
	char	*temp;
	char	*exit_code;

	exit_code = ft_itoa(ft_exit(0, 0, 0));
	if (!exit_code)
	{
		free(str);
		return (NULL);
	}
	temp = ft_insertstr(str, (*i)--, exit_code);
	(*i) += ft_strlen(exit_code);
	free(exit_code);
	free(str);
	return (temp);
}

char	*ft_expand_vars(char *str, size_t *i, t_shell *sh)
{
	if (str[*i] && str[*i] == '?')
		str = ft_expand_exit(str, i);
	else if (ft_isalnum(str[*i]) || str[*i] == '_')
		str = ft_expand_string(str, i, sh);
	return (str);
}
