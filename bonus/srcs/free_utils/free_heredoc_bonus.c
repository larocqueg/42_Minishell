/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_heredoc_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:05:55 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/22 18:26:16 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
	free_tokens(sh->token);
}

void	free_exit(t_shell *sh, char *end, int heredoc_i, char *prompt)
{
	int	i;

	i = 0;
	close(sh->heredoc_pipes[heredoc_i][1]);
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
	free_envp(sh);
	if (ft_exit(0, 0, 0) == -1)
		exit(130);
	else
		exit(0);
}
