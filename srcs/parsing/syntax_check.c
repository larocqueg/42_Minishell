/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:02:44 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/13 21:09:54 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		else if ((*temp)->type == TOFILE && !(*temp)->next)
		{
			ft_fprintf(2, "%s \'%s\'\n", REDIRECT_T, (*temp)->token);
			return (0);
		}
	}
	return (1);
}

int	is_first_dot(t_token *token)
{
	char	*temp;
	if (token->type != WORD)
		return (0);
	temp = remove_quotes(token->token);
	if (!temp)
	{
		ft_fprintf(2, "Not enough resources\n");
		return (1);
	}
	if (ft_strncmp(temp, ".", 2) == 0)
	{
		ft_exit_status(2, 1, 0);
		ft_fprintf(2, "%s '%s'\n", UNEXPECTED_T, temp);
		free(temp);
		return (1);
	}
	if (ft_strncmp(temp, "..", 3) == 0)
	{
		ft_exit_status(2, 1, 0);
		ft_fprintf(2, "%s '%s'\n", UNEXPECTED_T, temp);
		free(temp);
		return (1);
	}
	free(temp);
	return (0);
}

int	check_tokens(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		if (is_first_dot(token))
			return (0);
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
