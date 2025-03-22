/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:52:22 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/21 13:54:39 by rafaelfe         ###   ########.fr       */
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
	if (ft_strncmp(token, ">", 1) == 0)
		return (OVERWRITE);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(token, "<", 1) == 0)
		return (INFILE);
	if (ft_strncmp(token, ">", 1) == 0)
		return (TOFILE);
	if (ft_strncmp(token, "'", 1) == 0)
		return (SINGLEQ_ARG);
	return (WORD);
}

static void	extract_token(char *prompt, int *i, t_token **tokens)
{
	int		j;
	char	token[4096];
	char	quote;
	bool	expand;
	t_token	*new_token;

	j = 0;
	expand = true;
	if (prompt[*i] == '"' || prompt[*i] == '\'')
	{
		quote = prompt[(*i)++];
		if (quote == '\'')
			expand = false;
		token[j++] = quote;
		while (prompt[*i] && prompt[*i] != quote)
			token[j++] = prompt[(*i)++];
		if (prompt[*i] == quote)
			token[j++] = prompt[(*i)++];
	}
	else if (is_operator(prompt[*i]))
	{
		token[j++] = prompt[(*i)++];
		if ((token[0] == '>' && prompt[*i] == '>')
			|| (token[0] == '<' && prompt[*i] == '<'))
			token[j++] = prompt[(*i)++];
	}
	else
		while (prompt[*i] && !is_space(prompt[*i]) && !is_operator(prompt[*i]))
			token[j++] = prompt[(*i)++];
	token[j] = '\0';
	new_token = ft_tokennew(ft_strdup(token), get_token_type(token), expand);
	ft_token_addback(tokens, new_token);
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
		extract_token(prompt, &i, &tokens);
	}
	return (tokens);
}
