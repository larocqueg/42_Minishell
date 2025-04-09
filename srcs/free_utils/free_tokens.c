/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:59:35 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/07 21:00:58 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token	*token)
{
	t_token *temp;

	temp = token;
	while (token)
	{	temp = token -> next;
		free(token->token);
		free(token);
		token = temp;
	}
	token = NULL;
}
