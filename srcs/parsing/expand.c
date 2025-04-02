/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:03:03 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/02 18:39:01 by rafaelfe         ###   ########.fr       */
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

void	remove_quotes(t_token *token)
{
	char	quote;
	char	*result;
	int		i;
	int		j;

	if (!token->token)
		return ;
	result = malloc(sizeof(char) * ft_strlen(token->token) + 1);
	i = 0;
	j = 0;
	quote = '\0';
	while (token->token[i])
	{
		if ((token->token[i] == '\'' || token->token[i] == '"') && quote == '\0')
			quote = token->token[i++];
		else if (token->token[i] == quote)
		{
			i++;
			quote = '\0';
		}
		else
			result[j++] = token->token[i++];
	}
	result[j] = '\0';
	free(token->token);
	token->token = result;
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
char	*expand(char *str, bool in_quotes, bool in_single_quotes, t_shell *sh)
{
	char	*temp;
	size_t		i;
	char	*exit_str;
	char	*variable_name;

	exit_str = ft_itoa(g_exit_code);

	i = 0;
	while (str[i] && i < ft_strlen(str))
	{
		set_quotes(str[i], &in_single_quotes, &in_quotes);
		if (str[i] == '$' && !in_single_quotes)
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

void	expand_tokens(t_token *token, t_shell *sh)
{
	char	*temp;
	temp = NULL;

	while (token)
	{
		if (token->type == WORD)
		{
			temp = expand(token-> token, false, false, sh);
			token-> token = temp;
			remove_quotes(token);
		}
		token = token -> next;
	}
}
