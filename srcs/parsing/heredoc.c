/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:23:45 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/04 18:48:01 by rafaelfe         ###   ########.fr       */
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

static void	ft_create_heredoc_pipes(t_shell *sh, char *end, int i, bool quote)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("> ");
		if (!prompt)
		{
			close(sh->heredoc_pipes[i][1]);
			break ;
		}

		if (prompt && !ft_strncmp(prompt, end, ft_strlen(end) + 1))
		{
			close(sh->heredoc_pipes[i][1]);
			free(prompt);
			break ;
		}
		else
		{
			if (prompt[0] && !quote)
				prompt = expand(prompt, false, false, sh, true);
			ft_putstr_fd(prompt, sh->heredoc_pipes[i][1]);
			ft_putstr_fd("\n", sh->heredoc_pipes[i][1]);
		}
		if (prompt)
			free(prompt);
	}
}
int has_quotes(char *str)
{
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			return (1);
		str++;
	}
	return (0);
}
void	get_heredoc(t_shell *sh, t_token *token)
{
	int		i;
	t_token	*temp;
	char	*end;

	i = 0;
	temp = token;
	ft_heredoc_init(sh);
	while (temp)
	{
		if (temp->type == HERE_DOC)
		{
			end = remove_quotes(temp->next->token);
			ft_create_heredoc_pipes(sh, end, i, has_quotes(temp->next->token));
			i++;
		}
		temp = temp->next;
	}
}
