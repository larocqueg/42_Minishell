/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:05:03 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/10 21:05:07 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_heredoc_init(t_shell *sh)
{
	int	i = 0;

	sh->heredoc_pipes = malloc(sizeof(int *) * (sh->heredoc_count + 1));
	while (i < sh->heredoc_count)
	{
		sh->heredoc_pipes[i] = malloc(sizeof(int) * 2);
		sh->heredoc_pipes[i][0] = -1;
		sh->heredoc_pipes[i][1] = -1;
		i++;
	}
	sh->heredoc_pipes[i] = NULL;
}

static void	free_heredoc_pipes(t_shell *sh)
{
	int	i = 0;

	while (i < sh->heredoc_count)
	{
		if (sh->heredoc_pipes[i])
			free(sh->heredoc_pipes[i]);
		i++;
	}
	free(sh->heredoc_pipes);
}

static void	ft_create_heredoc_pipes(t_shell *sh, char *end, int i, bool quote)
{
	char	*prompt;
	char	*temp;

	while (1)
	{
		ft_fprintf(1, "> ");
		prompt = get_next_line(STDIN_FILENO);
		if (!prompt)
		{
			get_next_line(-1);
			ft_fprintf(2, "warning: here-document delimited by end-of-file ");
			ft_fprintf(2, "(wanted '%s')\n", end);
			close(sh->heredoc_pipes[i][1]);
			free_heredoc_pipes(sh);
			free_tokens(sh->token);
			free(end);
			break;
		}
		if (!ft_strncmp(prompt, end, ft_strlen(prompt) - 1) && prompt[0] != '\n')
		{
			get_next_line(-1);
			close(sh->heredoc_pipes[i][1]);
			free(prompt);
			free_heredoc_pipes(sh);
			free_tokens(sh->token);
			free(end);
			break;
		}
		if (prompt[0] && !quote)
		{
			temp = expand(prompt, sh, true);
			free(prompt);
			prompt = temp;
		}
		ft_putstr_fd(prompt, sh->heredoc_pipes[i][1]);
		//ft_putstr_fd("\n", sh->heredoc_pipes[i][1]);
		free(prompt);
	}
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

void	heredoc_signal_handler(int sig)
{
	if (sig)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		ft_exit_status(130, true, true);
	}
}

int	get_heredoc(t_shell *sh)
{
	int		i = 0;
	int		pid, status;
	t_token	*temp = sh->token;
	char	*end;

	if (sh->heredoc_count < 1)
		return (1);

	ft_heredoc_init(sh);
	while (temp)
	{
		if (temp->type == HERE_DOC)
		{
			end = remove_quotes(temp->next->token);
			pipe(sh->heredoc_pipes[i]);
			pid = fork();
			if (pid == 0)
			{
				int j = 0;
				free_envp(sh);
				while (j <= i)
				{
					if (sh->heredoc_pipes[j][0] != -1)
						close(sh->heredoc_pipes[j][0]);
					j++;
				}
				signal_default();
				signal(SIGINT, heredoc_signal_handler);
				signal(SIGQUIT, SIG_IGN);
				ft_create_heredoc_pipes(sh, end, i, has_quotes(temp->next->token));
				close(sh->original_stdin);
				close(sh->original_stdout);
				ft_exit_status(0, true, true);
			}
			else
			{
				signal(SIGINT, SIG_IGN);
				waitpid(pid, &status, 0);
			}
			if (WEXITSTATUS(status) == 130)
			{
				ft_exit_status(130, true, false);
				free(sh->prompt);
				free_tokens(sh->token);
				for (int k = 0; k < sh->heredoc_count; k++)
				{
					close(sh->heredoc_pipes[k][1]);
					close(sh->heredoc_pipes[k][0]);
					free(sh->heredoc_pipes[k]);
				}
				free(sh->heredoc_pipes);
				free(end);
				dup2(sh->original_stdin, STDIN_FILENO);
				dup2(sh->original_stdout, STDOUT_FILENO);
				return (0);
			}
			else
				close(sh->heredoc_pipes[i][1]);
			free(end);
			i++;
		}
		temp = temp->next;
	}
	/*for (int j = 0; j < sh->heredoc_count; j++)
	{
		if (sh->heredoc_pipes[j][0] != -1)
			close(sh->heredoc_pipes[j][0]);
	}*/
	dup2(sh->original_stdin, STDIN_FILENO);
	dup2(sh->original_stdout, STDOUT_FILENO);

	return (1);
}

/*
int	get_heredoc(t_shell *sh)
{
	int		i;
	t_token	*temp;
	char	*end;
	int		pid;
	int		status;
	pid = 0;
	status = 0;
	i = 0;
	if (sh->heredoc_count < 1)
		return (1);
	temp = sh->token;
	ft_heredoc_init(sh);
	pid = fork();
	if (pid == 0)
	{
		signal_default();
		signal(SIGINT, heredoc_signal_handler);
		signal(SIGQUIT, SIG_IGN);
		//signal(SIGPIPE, SIG_IGN);
		while (temp)
		{
			if (temp->type == HERE_DOC)
			{
				end = remove_quotes(temp->next->token);
				ft_create_heredoc_pipes(sh, end, i, has_quotes(temp->next->token));
				free(end);
				i++;
			}
			temp = temp->next;
		}
		ft_exit_status(0, 1, 1);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
	}
	if (WEXITSTATUS(status) == 130)
	{
		ft_exit_status(130, true, false);
		free(sh->prompt);
		free_tokens(sh->token);
		for (int i = 0; i < sh->heredoc_count; i++)
		{
			close(sh->heredoc_pipes[i][1]);
			close(sh->heredoc_pipes[i][0]);
			free(sh->heredoc_pipes[i]);
		}
		free(sh->heredoc_pipes);
		return (0);
	}
	else
	{
		for (int i = 0; i < sh->heredoc_count; i++)
			close(sh->heredoc_pipes[i][1]);
		return (1);

	}
}
*/
