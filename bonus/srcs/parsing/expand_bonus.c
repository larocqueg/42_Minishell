/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:03:03 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/22 18:26:16 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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

char	*expand(char *str, t_shell *sh, bool heredoc, size_t i)
{
	char	*result;
	bool	in_quotes;
	bool	in_single_quotes;

	if (!str)
		return (NULL);
	in_single_quotes = false;
	in_quotes = false;
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	while (i < ft_strlen(result))
	{
		set_quotes(result[i], &in_single_quotes, &in_quotes);
		if (result[i] && result[i] == '$' && (!in_single_quotes || heredoc))
		{
			i++;
			if (result[i] == '?' || ft_isalpha(result[i]) || result[i] == '_' )
				result = ft_expand_vars(result, &i, sh);
			if (!result)
				return (NULL);
		}
		i++;
	}
	return (result);
}

void	expand_tokens(t_shell *sh)
{
	char	*temp;
	t_token	*token;

	temp = NULL;
	token = sh->token;
	while (token)
	{
		if (token->type == WORD)
		{
			temp = expand(token->token, sh, false, 0);
			free(token->token);
			token->token = remove_quotes(temp);
			free(temp);
		}
		token = token -> next;
	}
}
