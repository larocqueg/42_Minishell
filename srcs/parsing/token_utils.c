/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:00:51 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/21 11:21:52 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_tokennew(char *str, int type)
{
	t_token	*n_token;

	n_token = (t_token *)malloc(sizeof(t_token));
	if (!n_token)
		return (NULL);
	n_token->token = str;
	n_token->type = type;
	n_token->next = NULL;
	return (n_token);
}
void	ft_token_addback(t_token **token, t_token *new)
{
	t_token	*temp;

	if (!new)
		return ;
	if (!*token)
	{
		*token = new;
		return ;
	}
	while (*token)
	{
		if ((*token)->next == NULL)
		{
			temp = (*token);
			break;
		}
		(*token) = (*token)->next;
	}
	temp->next = new;
}


