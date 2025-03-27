/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:52:22 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/27 23:21:43 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	extract_quotes(char *prompt, int i, char *token, int *j)
{
    char	quote;

    quote = prompt[i];
    token[(*j)++] = prompt[i++]; // Add the opening quote
    while (prompt[i] && prompt[i] != quote)
        token[(*j)++] = prompt[i++]; // Add characters inside the quotes
    if (prompt[i] == quote)
        token[(*j)++] = prompt[i++]; // Add the closing quote
    return (i);
}

int extract_token(char *prompt, int i, t_token **tokens)
{
	int j;
	char *token;
	t_token *new_token;

	j = 0;
	token = malloc(sizeof(char) * 4096);
	if (!token)
		return (i);

	while (prompt[i] && !is_space(prompt[i]))
	{
		if (is_operator(prompt[i]))
		{
			if (j > 0)
				break;
			token[j++] = prompt[i++];
			if (prompt[i] == token[j - 1])
				token[j++] = prompt[i++];
			break;
		}
		else if (prompt[i] == '\'' || prompt[i] == '"')
			i = extract_quotes(prompt, i, token, &j);
		else
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
