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
	int		i;

	i = 0;
	sh->heredoc_pipes = malloc(sizeof(int *) * ((sh->heredoc_count) + 1));
	while (i < sh->heredoc_count)
	{
		i++;
	}
}

static void	ft_create_heredoc_pipes(t_shell *sh, char *end, int i, bool quote)
{
	char	*prompt;
	char	*temp;
	int		j;

	j = 0;
	while (1)
	{
		prompt = readline("> ");
		if (!prompt)
		{
			ft_fprintf(2, "warning: here-document at line 1 delimited by end-of-file ");
			ft_fprintf(2, "(wanted '%s')\n", end);
			close(sh->heredoc_pipes[i][1]);
			while(j < sh->heredoc_count)
				free(sh->heredoc_pipes[j++]);
			free(sh->heredoc_pipes);
			free_tokens(sh->token);
			free(end);
			break;
		}

		if (prompt && !ft_strncmp(prompt, end, ft_strlen(end) + 1))
		{
			close(sh->heredoc_pipes[i][1]);
			while(j < sh->heredoc_count)
				free(sh->heredoc_pipes[j++]);
			free(sh->heredoc_pipes);
			free_tokens(sh->token);
			free(prompt);
			free(end);
			break ;
		}
		else
		{
			if (prompt[0] && !quote)
			{
				temp = expand(prompt, sh, true);
				free(prompt);
				prompt = temp;
			}
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
void heredoc_signal_handler(int sig)
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
	while (temp)
	{
		if (temp->type == HERE_DOC)
		{
			end = remove_quotes(temp->next->token);
			sh->heredoc_pipes[i] = malloc(sizeof(int) * 2);
			pipe(sh->heredoc_pipes[i]);
			pid = fork();
			if (pid == 0)
			{
				free_envp(sh);
				close(sh->heredoc_pipes[i][0]);
				signal_default();
				signal(SIGINT, heredoc_signal_handler);
				signal(SIGQUIT, SIG_IGN);
				ft_create_heredoc_pipes(sh, end, i, has_quotes(temp->next->token));
				close(sh->original_stdin);
				close(sh->original_stdout);
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
				perror("chegou aqui!1");
				for (int i = 0; i < sh->heredoc_count; i++)
				{
					close(sh->heredoc_pipes[i][1]);
					close(sh->heredoc_pipes[i][0]);
				//ak	free(sh->heredoc_pipes[i]);
					perror("chegou aqui!2");
					perror("chegou aqui3!");
				}
				//free(sh->heredoc_pipes);
				free(end);
				perror("chegou aqui!4");
				return (0);
			}
			else
			{
				close(sh->heredoc_pipes[i][1]);
			}
			free(end);
			i++;
		}
		temp = temp->next;
	}
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
