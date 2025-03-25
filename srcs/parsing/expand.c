/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:03:03 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/25 20:29:32 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_tokens(t_token *token)
{
	char	*temp;
	t_token	*head;

	head = token;
	while (token)
	{
		if (token->type == WORD)
		{
			temp = expand(token-> token);
			if (!temp)
				//free all tokens
			free(token->token);
			token -> token = temp;
		}
		token = token -> next;
	}
}
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
char	*expand(char *str)
{
	bool	expand;
	bool	in_quotes;
	bool	in_single_quotes;
	char	*temp;

	int	i;
	while (str[i])
	{
		set_quotes(str[i], &in_single_quotes, &in_quotes);
		if (str[i] = '$' && !in_single_quotes)
		{
			
		}

		i++;
	}
}
