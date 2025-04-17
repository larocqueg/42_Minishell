/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:05:55 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/15 20:05:21 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pipes(t_shell *sh)
{
	int	i;

	i = 0;
	if (sh->heredoc_count == 0)
		return ;
	while (sh->heredoc_pipes[i])
	{
		close(sh->heredoc_pipes[i][0]);
		free(sh->heredoc_pipes[i]);
		i++;
	}
	free(sh->heredoc_pipes);
	sh->heredoc_pipes = NULL;
}
