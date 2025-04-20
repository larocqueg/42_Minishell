/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:47:41 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/20 18:47:42 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	free_tokens(t_token	*token)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token;
	while (token)
	{
		temp = token -> next;
		free(token->token);
		free(token);
		token = temp;
	}
	token = NULL;
}

void	ft_free_tokenize(t_token *token, char *prompt)
{
	free(prompt);
	free_tokens(token);
}
