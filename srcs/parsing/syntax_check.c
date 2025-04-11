/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:02:44 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/10 21:09:29 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		ft_exit_status(2, true, false);
		return (0);
	}
	return (1);
}

static int	is_first_pipe(t_token *token)
{
	if (token->type == PIPE)
	{
		ft_fprintf(2, "%s '|'\n", UNEXPECTED_T);
		ft_exit_status(2, true, false);
		return (1);
	}
	return (0);
}

static int	check_valid_operators(t_token **temp)
{
	bool	pipe;

	pipe = false;
	if ((*temp)->type != WORD)
	{
		if ((*temp)->type == PIPE)
			pipe = true;
		(*temp) = (*temp)-> next;
		if (!(*temp))
		{
			ft_fprintf(2, "%s \\n\n", UNEXPECTED_T);
			return (0);
		}
		else if (((*temp)->type == PIPE && pipe)
				|| ((*temp)->type != WORD && !pipe))
		{
			ft_fprintf(2, "%s '%s'\n", UNEXPECTED_T, (*temp)->token);
			return (0);
		}
	}
	return (1);
}

int	check_tokens(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (is_first_pipe(token))
			return (0);
		if (!check_valid_operators(&temp))
			return (0);
		temp = temp -> next;
	}
	return (1);
}

int	check_syntax(t_shell *sh)
{
	char	*temp;
	t_token	*token;

	token = sh->token;
	temp = sh->prompt;
	if (!check_quotes(temp))
	{
		free_tokens(sh->token);
		free(sh->prompt);
		return (0);
	}
	if (!check_tokens(token))
	{
		free_tokens(sh->token);
		free(sh->prompt);
		ft_exit_status(2, true, false);
		return (0);
	}
	free(sh->prompt);
	return (1);
}
