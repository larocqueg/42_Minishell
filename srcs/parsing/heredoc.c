/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:22:26 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/18 15:33:20 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_heredoc_child(t_shell *sh, t_token *token, int heredoc_i)
{
	signal(SIGINT, ft_heredoc_signal_handler);
	ft_get_heredoc(sh, remove_quotes(token->next->token),
		heredoc_i, has_quotes(token->next->token));
}

int	handle_heredoc_parent(t_shell *sh, int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		ft_exit_status(WEXITSTATUS(status), true, false);
		if (ft_exit_status(0, 0, 0) == 130)
		{
			handle_exit(sh);
			return (0);
		}
	}
	return (1);
}

int	get_heredoc(t_shell *sh)
{
	t_token	*token;
	int		heredoc_i;
	int		pid;
	int		i;

	i = 0;
	if (sh->heredoc_count < 1)
		return (1);
	if (!ft_heredoc_init(sh))
		return (0);
	heredoc_i = 0;
	pid = -1;
	token = sh->token;
	while (token)
	{
		if (!here_doc_loop(token, sh, &heredoc_i, &pid))
			return (0);
		token = token->next;
	}
	while (sh->heredoc_pipes[i])
	{
		close(sh->heredoc_pipes[i][1]);
		i++;
	}
	return (1);
}

void	start_heredoc(t_shell *sh, int heredoc_i)
{
	int	i;

	i = 0;
	close(sh->original_stdin);
	close(sh->original_stdout);
	while (sh->heredoc_pipes[i])
	{
		close(sh->heredoc_pipes[i][0]);
		if (i != heredoc_i)
		{
			close (sh->heredoc_pipes[i][1]);
		}
		i++;
	}
}

void	ft_get_heredoc(t_shell *sh, char *end, char heredoc_i, bool quote)
{
	char	*prompt;
	char	*temp;

	start_heredoc(sh, heredoc_i);
	prompt = NULL;
	while (1)
	{
		prompt = readline("> ");
		if (ft_exit_status(0, 0, 0) == -1)
			free_exit(sh, end, heredoc_i, prompt);
		if (!not_prompt(sh, end, heredoc_i, prompt))
			continue ;
		if (!ft_strncmp(prompt, end, ft_strlen(end) + 1) && prompt[0] != '\n')
			free_exit(sh, end, heredoc_i, prompt);
		if (prompt[0] && !quote)
		{
			temp = expand(prompt, sh, true, 0);
			free(prompt);
			prompt = temp;
		}
		if (prompt)
			ft_putstr_fd(prompt, sh->heredoc_pipes[heredoc_i][1]);
		ft_putstr_fd("\n", sh->heredoc_pipes[heredoc_i][1]);
		free(prompt);
	}
}
