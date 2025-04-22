/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:59:35 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/22 18:26:16 by rafaelfe         ###   ########.fr       */
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
