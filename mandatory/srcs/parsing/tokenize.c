/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:20:53 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/12 18:11:47 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_type	get_token_type(char *token, t_shell *sh)
{
	if (!token)
		return (WORD);
	if (ft_strncmp(token, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(token, "<<", 2) == 0)
	{
		sh->heredoc_count++;
		return (HERE_DOC);
	}
	if (ft_strncmp(token, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(token, "<", 1) == 0)
		return (INFILE);
	if (ft_strncmp(token, ">", 1) == 0)
		return (TOFILE);
	return (WORD);
}

static int	extract_quotes(char *prompt, int i)
{
	char	quote;

	quote = prompt[i++];
	while (prompt[i] && prompt[i] != quote)
		i++;
	if (prompt[i] == quote)
		i++;
	return (i);
}

static int	extract_word(char *prompt, int i)
{
	while (prompt[i] && !is_space(prompt[i]) && !is_operator(prompt[i]))
	{
		if ((prompt[i] == '\'' || prompt[i] == '"'))
			i = extract_quotes(prompt, i);
		else
			i++;
	}
	return (i);
}

static int	extract_token(int start, int i, t_token **tokens, t_shell *sh)
{
	char	*token;
	t_token	*new_token;

	if (!is_operator(sh->prompt[i]))
	{
		start = i;
		i = extract_word(sh->prompt, i);
		token = ft_strndupmod(sh->prompt, start, i - 1);
	}
	else
	{
		start = i++;
		if (sh->prompt[i] == sh->prompt[i - 1])
			i++;
		token = ft_strndupmod(sh->prompt, start, i - 1);
	}
	if (!token)
		return (-1);
	new_token = ft_tokennew(token, get_token_type(token, sh));
	if (!new_token)
		return (free(token), -1);
	ft_token_addback(tokens, new_token);
	free(token);
	return (i);
}

int	tokenize(char *prompt, t_shell *sh)
{
	int		i;
	int		j;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (prompt[i] && i < ARG_MAX)
	{
		j = i;
		while (is_space(prompt[i]))
			i++;
		if (i == j)
		{
			if ((prompt[i] == '-' || prompt[i] == '!') && ft_type(tokens) == 2)
				i++;
		}
		if (!prompt[i])
			break ;
		i = extract_token(-1, i, &tokens, sh);
		if (i == -1)
			ft_free_tokenize(tokens, sh->prompt);
	}
	sh->token = tokens;
	return (1);
}
