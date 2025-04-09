/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:20:53 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/07 20:56:36 by rafaelfe         ###   ########.fr       */
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
	if (is_var(token))
		return (VAR);
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

int	extract_token(char *prompt, int i, t_token **tokens, t_shell *sh)
{
	int		start;
	char	*token;
	t_token	*new_token;

	start = 0;
	token = NULL;
	while (prompt[i] && !token)
	{
		if (!is_operator(prompt[i]))
		{
			start = i;
			i = extract_word(prompt, i);
			token = ft_strndupmod(prompt, start, i - 1); // malloc
		}
		else
		{
			start = i++;
			if (prompt[i] == prompt[i - 1])
				i++;
			token = ft_strndupmod(prompt, start, i - 1); // malloc
		}
		if (!token)
			return (-1);
	}
	new_token = ft_tokennew(token, get_token_type(token, sh)); //malloc
	ft_token_addback(tokens, new_token); //malloc
	return (free(token), i);
}

int	tokenize(char *prompt, t_shell *sh)
{
	int		i;
	t_token	*tokens;

	i = 0;
	tokens = NULL;
	while (prompt[i] && i < ARG_MAX)
	{
		while (is_space(prompt[i]))
			i++;
		if (!prompt[i])
			break ;
		i = extract_token(prompt, i, &tokens, sh);
		if (i == -1)
		{
			free_tokens(tokens);
			free(sh->prompt);
			return (0);
		}
	}
	sh->token = tokens;
	return (1);
}
