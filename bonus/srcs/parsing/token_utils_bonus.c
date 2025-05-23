/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:00:51 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/19 13:57:32 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

t_token	*ft_tokennew(char *str, int type)
{
	t_token	*n_token;

	if (!str)
		return (NULL);
	n_token = (t_token *)malloc(sizeof(t_token));
	if (!n_token)
		return (NULL);
	n_token->token = ft_strdup(str);
	if (!n_token->token)
	{
		free(n_token);
		return (NULL);
	}
	n_token->type = type;
	if (n_token->type == WORD && has_wildcard(str))
		n_token->wildcard = true;
	else
		n_token->wildcard = false;
	n_token->next = NULL;
	return (n_token);
}

void	ft_token_addback(t_token **token, t_token *new_token)
{
	t_token	*temp;

	if (!new_token)
		return ;
	if (!*token)
	{
		*token = new_token;
		return ;
	}
	temp = *token;
	while (temp->next)
		temp = temp->next;
	temp->next = new_token;
}

int	is_operator(char prompt)
{
	if (prompt == '|' || prompt == '>' || prompt == '<')
		return (1);
	return (0);
}

int	is_space(char prompt)
{
	if (prompt == 32 || (prompt >= 9 && prompt <= 13))
		return (1);
	return (0);
}

int	is_var(char *token)
{
	int	i;

	if (!token || !*token)
		return (0);
	i = 1;
	if (!ft_isalpha(token[0]) && token[0] != '_')
		return (0);
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
		i++;
	if (token[i] == '=')
		return (1);
	return (0);
}
