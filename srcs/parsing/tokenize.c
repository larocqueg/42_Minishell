/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:52:22 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/28 21:28:37 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_var(char *token)
{
	int	i;

	i = 1;
	if (!ft_isalpha(token[0]) && token[0] != '_')
		return (0);
	while (token[i])
	{
		if (ft_isalnum(token[i]) || token[i]=='_')
			i++;
		if (token[i] == '=')
			return (1);
		else
			return (0);
	}
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
	if (is_var(token))
		return (VAR);
	return (WORD);
}

static int	extract_quotes(char *prompt, int i)
{
	char	quote;

	quote = prompt[i++];
	while(prompt[i] && prompt[i] != quote)
		i++;
	if (prompt[i] == quote)
		i++;
	return(i);
}

static int	extract_word(char *prompt, int i)
{
	char	quote;

	quote = '\0';
	while (prompt[i] && !is_space(prompt[i]) && !is_operator(prompt[i]))
	{
		if ((prompt[i] == '\'' || prompt[i] == '"') && quote == '\0')
			extract_quotes(prompt, i);
		i++;
	}
	return (i);
}

int extract_token(char *prompt, int i, t_token **tokens)
{
	int		start;
	char	*token;
	t_token	*new_token;

	start = 0;
	while (prompt[i] && !is_space(prompt[i]))
	{
		if (is_operator(prompt[i]))
		{
			start = i;
			i++;
			if (prompt[i] == prompt[i - 1])
				i++;
		}
		else
		{
			start = i;
			i = extract_word(prompt, i);
		}
	}
	token = ft_strndupmod(prompt, start, i - 1);
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
