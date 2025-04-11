/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:05:55 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/11 19:06:07 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pipes(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->heredoc_pipes && sh->heredoc_pipes[i])
	{
		close(sh->heredoc_pipes[i][0]);
		free(sh->heredoc_pipes[i]);
		i++;
	}
	free(sh->heredoc_pipes);
	sh->heredoc_pipes = NULL;
}
