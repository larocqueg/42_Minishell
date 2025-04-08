/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:03:03 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/08 19:08:54 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	set_quotes(char c, bool *in_single_quotes, bool *in_quotes)
{
	if (c == 39 && !*in_quotes)
	{
		if (*in_single_quotes)
			*in_single_quotes = false;
		else
			*in_single_quotes = true;
	}
	else if (c == 34 && !*in_single_quotes)
	{
		if (*in_quotes)
			*in_quotes = false;
		else
			*in_quotes = true;
	}
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
	i = 0;
	j = 0;
	quote = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == '\0')
			quote = str[i++];
		else if (str[i] == quote)
		{
			i++;
			quote = '\0';
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

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
char	*expand(char *str, bool in_quotes, bool in_single_quotes, t_shell *sh, bool heredoc)
{
	char	*temp;
	size_t		i;
	char	*exit_str;
	char	*variable_name;

	exit_str = ft_itoa(ft_exit_status(0, false, false));

	i = 0;
	while (str[i] && i < ft_strlen(str))
	{
		set_quotes(str[i], &in_single_quotes, &in_quotes);
		if (str[i] == '$' && (!in_single_quotes || heredoc))
		{
			i++;
			if (str[i] == '?')
			{
				temp = ft_insertstr(str, i--, exit_str);
				free(str);
				str = temp;
				i += ft_strlen(exit_str);
			}
			else if (!ft_isdigit(str[i]) && (ft_isalnum(str[i]) || str[i] == '_'))
			{
				variable_name = extract_variable(str, i);
				temp = ft_insertstr(str, i--, ft_get_env(variable_name, sh->envp));
				free(str);
				str = temp;
				if (ft_get_env(variable_name, sh->envp))
					i += (ft_strlen(ft_get_env(variable_name, sh->envp)) - 1);
			}
		}
		i++;
	}
	free(exit_str);
	if (ft_strlen(str) == 0)
	{
		str = NULL;
	}
	return (str);
}

void	expand_tokens(t_shell *sh)
{
	char	*temp;
	t_token *token;
	temp = NULL;

	token = sh->token;
	while (token)
	{
		if (token->type == WORD)
		{
			temp = expand(token->token, false, false, sh, false);
			//free(token->token);
			token->token = remove_quotes(temp);
			free(temp);
		}
		token = token -> next;
	}
}
