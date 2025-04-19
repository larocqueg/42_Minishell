/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:11:10 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/17 15:13:27 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	ft_type(t_token *tokens)
{
	if (!tokens)
		return (0);
	while (tokens)
	{
		if (tokens->next == NULL)
			break ;
		tokens = tokens->next;
	}
	return (tokens->type);
}
