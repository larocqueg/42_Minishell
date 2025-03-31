/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:23:45 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/03/31 19:57:11 by rafaelfe         ###   ########.fr       */
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
		pipe(sh->heredoc_pipes[i]);
		i++;
	}
}

static void	ft_create_heredoc_pipes(t_shell *sh, char *end, int i)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("> ");
		if (!prompt)
			printf("Error: EOF\n");

		if (prompt && !ft_strncmp(prompt, end, ft_strlen(end) + 1))
		{
			close(sh->heredoc_pipes[i][1]);
			free(prompt);
			break ;
		}
		else
		{
			prompt = expand(prompt, false, false);
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
	//int		pid;
	i = 0;
	temp = token;
	ft_heredoc_init(sh);
	//pid = fork();
	//if (pid != 0)
	//{
		//wait(NULL);
		//return ;
	//}
	//if (pid == 0)
	//{
		while (temp)
		{
			if (temp->type == HERE_DOC)
			{
				ft_create_heredoc_pipes(sh, temp->next->token, i);
				i++;
			}
			temp = temp->next;
		}
		//exit(0);
	}
	///i = 0;
	//while(i < sh->heredoc_count)
	//{
		//close(sh->heredoc_pipes[i][1]);
		//i++;
	//}
//}
