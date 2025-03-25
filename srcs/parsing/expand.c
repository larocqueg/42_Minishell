/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:03:03 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/25 16:47:13 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_tokens(t_token *token)
{
	char	*temp;

	while (token)
	{
		if (token ->type = WORD)
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

char	*expand(char *str)
{
	bool	expand;
	bool	in_quotes;
	bool	in_single_quotes;
	char	*temp;

	int	i;
	while (str[i])
	{
	}
}
