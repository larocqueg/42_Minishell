/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:52:22 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/25 19:41:26 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_operator(char prompt)
{
	if (prompt == '\'' || prompt == '"' || prompt == '|'
		|| prompt == '>' || prompt == '<')
		return (1);
	return (0);
}

static int	is_space(char prompt)
{
	if (prompt == 32 || (prompt >= 9 && prompt <= 13))
		return (1);
	return (0);
}

static t_type	get_token_type(char *token)
{
	if (!token)
		return (WORD);
	if (ft_strncmp(token, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(token, "<<", 2) == 0)
		return (HERE_DOC);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(token, "<", 1) == 0)
		return (INFILE);
	if (ft_strncmp(token, ">", 1) == 0)
		return (TOFILE);
	return (WORD);
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

int	extract_token(char *prompt, int i, t_token **tokens)
{
	int		j;
	char*	token;
	t_token	*new_token;
	bool	in_quotes;
	bool	in_single_quotes;

	in_quotes = false;
	in_single_quotes = false;
	j = 0;
	token = malloc(sizeof(char) * 4096);

	while (prompt[i])
	{
		set_quotes(prompt[i], &in_single_quotes, &in_quotes);
		if ((is_space(prompt[i]) || is_operator(prompt[i])) && (!in_quotes && !in_single_quotes))
			break;
		token[j++] = prompt[i++];
	}
	if (is_operator(prompt[i]))
	{
		token[j++] = prompt[i++];
		if (prompt[i] == token[j])
			token[j++] = prompt[i++];
	}

	token[j] = '\0';
	new_token = ft_tokennew(token, get_token_type(token));
	ft_token_addback(tokens, new_token);
	free(token);
	return (i);
}

t_token	*tokenize(char *prompt)
{
	int		i;
	t_token	*tokens;
	i = 0;
	tokens = NULL;
	while (prompt[i])
	{
		while (is_space(prompt[i]))
			i++;
		if (!prompt[i])
			break ;
		i = extract_token(prompt, i, &tokens);
	}
	return (tokens);
}
