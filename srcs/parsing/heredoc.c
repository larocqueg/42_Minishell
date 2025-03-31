/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:23:45 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/03/31 17:50:22 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_heredoc_init(t_shell *sh)
{
	int		i;

	i = 0;
	sh->heredoc_pipes = malloc(sizeof(int *) * (sh->heredoc_count));
	while (i < sh->heredoc_count)
	{
		sh->heredoc_pipes[i] = malloc(sizeof(int) * 2);
		if(pipe(sh->heredoc_pipes[i]) == -1)
		i++;
	}
}

static void	ft_create_heredoc_pipes(t_shell *sh, char *end, int i)
{
	char	*prompt;

	if (end[0] == '\'' || end[0] == '"')
		end = ft_strndupmod(end, 1, ft_strlen(end) - 1);
	while (1)
	{
		prompt = readline(">" );
		if (!ft_strncmp(prompt, end, ft_strlen(prompt)))
		{
			free(prompt);
			break ;
		}
		else
		{
			ft_putstr_fd(prompt, sh->heredoc_pipes[i][1]);
			ft_putstr_fd("\n", sh->heredoc_pipes[i][1]);
		}
		free(prompt);
	}
}
void	get_heredoc(t_shell *sh, t_token *token)
{
	int		i;
	t_token	*temp;
	int	pid = 0;
	ft_heredoc_init(sh);
	pid = fork();
	i = 0;
	temp = token;
	if (pid == 0)
	{
		while(temp)
		{
			if (temp->type == HERE_DOC)
			{
				ft_create_heredoc_pipes(sh, temp->next->token, i);
				i++;
			}
			temp = temp->next;
		}
		exit (0);
	}
	else
	{
		 i = 0;
		while (i < sh->heredoc_count)
		{
			close(sh->heredoc_pipes[i][1]);
			i++;
		}
		wait(NULL);
	}

}
