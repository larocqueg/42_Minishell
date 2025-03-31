/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:23:45 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/03/31 14:39:00 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_heredoc_init(t_shell *sh)
{
	int		i;

	i = 0;
	sh->heredoc_pipes = malloc(sizeof(int **) * (sh->heredoc_count));
	while (i < sh->heredoc_count)
	{
		sh->heredoc_pipes[i] = malloc(sizeof(int) * 2);
		i++;
	}
}

static void	ft_create_heredoc_pipes(t_shell *sh, char *end, int i)
{
	char	*dest;
	char	*prompt;

	dest = ft_strdup("");
	if (end[0] == '\'' || end[0] == '"')
		end = ft_strndupmod(end, 1, ft_strlen(end) - 1);
	pipe(sh->heredoc_pipes[i]);
	while (1)
	{
		prompt = readline(">" );
		if (!ft_strncmp(prompt, end, ft_strlen(end) - 1))
		{
			close(sh->heredoc_pipes[i][1]);
			free(prompt);
			break ;
		}
		else
		{
			ft_putstr_fd(prompt, sh->heredoc_pipes[i][0]);
			ft_putstr_fd("\n", sh->heredoc_pipes[i][0]);
		}
		free(prompt);
	}
}
void	get_heredoc(t_shell *sh, t_token *token)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = token;
	ft_heredoc_init(sh);
	while(temp)
	{
		if (temp->type == HERE_DOC)
		{
			ft_create_heredoc_pipes(sh, temp->next->token, 0);
			i++;
		}
		temp = temp->next;
	}
}
