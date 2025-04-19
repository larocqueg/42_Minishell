/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 21:03:23 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/19 11:33:21 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	ft_ischar(int *i)
{
	(*i)++;
	return ('\0');
}

char	*remove_quotes(char *str)
{
	char	quote;
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == '\0')
			quote = str[i++];
		else if (str[i] == quote)
			quote = ft_ischar(&i);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*ft_insertstr(char	*string, size_t index, char *substr)
{
	int		total_len;
	char	*after_str;
	char	*result;

	total_len = ft_strlen(string) + ft_strlen(substr) + 1;
	result = malloc(sizeof(char) * total_len);
	if (!result)
		return (NULL);
	after_str = NULL;
	ft_strlcpy(result, string, index);
	while (ft_isalnum(string[index]) || string[index] == '_')
		index++;
	if (string[index] == '?' && string[index - 1] == '$')
		index++;
	if (index <= ft_strlen(string))
		after_str = string + index;
	if (ft_strlen(substr) > 0)
		ft_strlcat(result, substr, total_len);
	ft_strlcat(result, after_str, total_len);
	return (result);
}

int	check_quotes(char *prompt)
{
	int	quote;
	int	i;

	quote = '\0';
	i = 0;
	while (prompt[i])
	{
		if ((prompt[i] == '\"' || prompt[i] == '\''))
		{
			if (!quote)
				quote = prompt[i];
			else if (prompt[i] == quote)
				quote = '\0';
		}
		i++;
	}
	if (quote != '\0')
	{
		write(2, "minishell: syntax error: unclosed quotes\n", 41);
		ft_exit(2, true, false);
		return (0);
	}
	return (1);
}

int	has_equals(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
