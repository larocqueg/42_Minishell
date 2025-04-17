/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:05:55 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/17 20:53:29 by rafaelfe         ###   ########.fr       */
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

void	handle_exit(t_shell *sh)
{
	int	j;

	j = 0;
	while (sh->heredoc_pipes[j])
	{
		close(sh->heredoc_pipes[j][0]);
		close(sh->heredoc_pipes[j][1]);
		free(sh->heredoc_pipes[j]);
		j++;
	}
	free(sh->heredoc_pipes);
	sh->heredoc_count = 0;
	write(1, "\n", 1);
	free_tokens(sh->token);
}

void	free_exit(t_shell *sh, char *end, int heredoc_index, char *prompt)
{
	int	i;

	i = 0;
	close(sh->heredoc_pipes[heredoc_index][1]);
	while (sh->heredoc_pipes[i])
	{
		free(sh->heredoc_pipes[i]);
		i++;
	}
	if (prompt)
		free(prompt);
	free(sh->heredoc_pipes);
	free_tokens(sh->token);
	free(end);
	if (ft_exit_status(0, 0, 0) == -1)
		exit(130);
	else
		exit(0);
}


