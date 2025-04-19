/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:50:22 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/18 16:13:40 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	here_doc_loop(t_token *token, t_shell *sh, int *heredoc_i, int *pid)
{
	if (token->type == HERE_DOC)
	{
		(*pid) = fork();
		if ((*pid) == -1)
		{
			handle_exit(sh);
			return (0);
		}
		if ((*pid) == 0)
			handle_heredoc_child(sh, token, *heredoc_i);
		else
		{
			if (!handle_heredoc_parent(sh, (*pid)))
				return (0);
		}
		(*heredoc_i)++;
	}
	return (1);
}

int	has_quotes(char *str)
{
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			return (1);
		str++;
	}
	return (0);
}

int	ft_heredoc_init(t_shell *sh)
{
	int	i;

	i = 0;
	sh->heredoc_pipes = malloc(sizeof(int *) * (sh->heredoc_count + 1));
	if (!sh->heredoc_pipes)
		return (0);
	while (i < sh->heredoc_count)
	{
		sh->heredoc_pipes[i] = malloc(sizeof(int) * 2);
		if (!sh->heredoc_pipes[i])
			return (0);
		if (pipe(sh->heredoc_pipes[i]) == -1)
		{
			i = 0;
			while (sh->heredoc_pipes[i])
				free(sh->heredoc_pipes[i++]);
			free(sh->heredoc_pipes);
			return (0);
		}
		i++;
		sh->heredoc_pipes[i] = NULL;
	}
	signal(SIGINT, ft_heredoc_parent_signal_handler);
	return (1);
}

int	not_prompt(t_shell *sh, char *end, int heredoc_i, char *prompt)
{
	if (!prompt)
	{
		ft_fprintf(2, "warning: here-document delimited by end-of-file ");
		ft_fprintf(2, "(wanted '%s')\n", end);
		free_exit(sh, end, heredoc_i, NULL);
	}
	return (1);
}
