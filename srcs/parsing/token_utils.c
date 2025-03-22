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

t_token	*ft_tokennew(char *str, int type, bool expand)
{
	t_token	*n_token;

	n_token = (t_token *)malloc(sizeof(t_token));
	if (!n_token)
		return (NULL);
	if (!str)
		return (free(n_token), NULL);
	n_token->token = str;
	n_token->type = type;
	n_token->next = NULL;
	n_token->expand = expand;
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


