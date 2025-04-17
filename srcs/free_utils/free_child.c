/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:55:12 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/17 18:59:15 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_child_pipes(t_shell *sh)
{
	int	i;

	if (sh->heredoc_count > 0)
	{
		i = 0;
		while (sh->heredoc_pipes[i])
		{
			close(sh->heredoc_pipes[i][0]);
			free(sh->heredoc_pipes[i]);
			i++;
		}
		free(sh->heredoc_pipes);
	}
}
