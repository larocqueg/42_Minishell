/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:20:53 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/10 21:04:31 by gde-la-r         ###   ########.fr       */
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
		return (-1);
	ft_token_addback(tokens, new_token);
	return (i);
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
		i = extract_token(-1, i, &tokens, sh);
		if (i == -1)
		{
			free_tokens(tokens);
			free(sh->prompt);
			return (0);
		}
	}
	sh->token = tokens;
<<<<<<< HEAD
	if (!sh->DEBUG)
		return 1;

	t_token *temp;
	temp = tokens;

	printf("-----TOKENS------------\n");
	while (temp)
	{
		printf("token->token: '%s', token->type= %d\n", temp->token, temp->type);
		temp = temp -> next;
	}
	printf("-----ENDTOKENS---------\n");
=======
>>>>>>> master
	return (1);
}
