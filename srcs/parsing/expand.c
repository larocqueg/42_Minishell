/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:03:03 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/26 14:06:50 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	set_quotes(char c, bool *in_single_quotes, bool *in_quotes)
{
	if (c == 39 && !in_quotes)
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
char	*extract_variable(char *str, int i)
{
	char *variable;
	int	j;
	j = i;
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	if (j >= i)
		return (ft_strndupmod(str, i, --j));
	return (NULL);
}
char	*expand(char *str, bool in_quotes, bool in_single_quotes)
{
	bool	expand;
	char	*temp;
	int		i;
	char	*exit_str;
	char	*variable_name;

	exit_str = ft_itoa(exit_code);

	i = 0;
	while (str[i])
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
			else if (!ft_isdigit(str[i]) && ft_isalnum(str[i]) || str[i] == '_')
			{
				variable_name = extract_variable(str, i);
				temp = ft_insertstr(str, i--, getenv(variable_name));
				free(str);
				str = temp;
				if (getenv(variable_name))
					i += ft_strlen(getenv(variable_name));
			}
		}
		i++;
	}
	return (str);
}

void	expand_tokens(t_token *token)
{
	char	*temp;
	t_token	*head;

	head = token;
	while (token)
	{
		if (token->type == WORD)
		{
			temp = expand(token-> token, false, false);
			if (!temp)
				//free all tokens
			free(token->token);
			token -> token = temp;
		}
		token = token -> next;
	}

}
