/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:22:26 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/17 18:10:42 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_get_heredoc(t_shell *sh, char *end, char	heredoc_index, bool quote);

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

static int	ft_heredoc_init(t_shell *sh)
{
	int	i;

	i = 0;
	ft_fprintf(2, "heredoc_count = %d\n", sh->heredoc_count);
	sh->heredoc_pipes = malloc(sizeof(int *) * (sh->heredoc_count + 1));
	while (i < sh->heredoc_count)
	{
		sh->heredoc_pipes[i] = malloc(sizeof(int) * 2);
		pipe(sh->heredoc_pipes[i]);
		i++;
	}
	sh->heredoc_pipes[i] = NULL;
	return (1);
}


void	ft_heredoc_signal_handler(int sig)
{
	ft_exit_status(-1, true, false);
	close(STDIN_FILENO);
}

int	get_heredoc(t_shell *sh)
{
	t_token *token;
	int		heredoc_index;
	int		pid;
	int		status;

	if (sh->heredoc_count == 0)
		return (1);
	status = 0;
	heredoc_index = 0;
	pid = -1;
	token = sh->token;
	ft_heredoc_init(sh);
	while (token)
	{
		if (token->type == HERE_DOC)
		{
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				exit(1);
			}
			if (pid == 0)
			{
				free_envp(sh);
				signal(SIGINT, ft_heredoc_signal_handler);
				ft_get_heredoc(sh, remove_quotes(token->next->token), heredoc_index, has_quotes(token->next->token));
			}
			else
			{
				waitpid(pid, &status, 0);
				if (WIFEXITED(status))
				{
					ft_exit_status(WEXITSTATUS(status), true, false);
					if (WEXITSTATUS(status) == 130)
					{
						for (int j = 0; sh->heredoc_pipes[j]; j++)
						{
							close(sh->heredoc_pipes[j][0]);
							close(sh->heredoc_pipes[j][1]);
							free(sh->heredoc_pipes[j]);
						}
						free(sh->heredoc_pipes);
						sh->heredoc_count = 0;
						write(1, "\n a", 1);
						free_tokens(sh->token);
						return (0);
					}
					else if (WEXITSTATUS(status) != 0)
					{
						ft_fprintf(2, "exited with code %d\n", WEXITSTATUS(status) + 128);
					}
				}
			}

			heredoc_index++;
		}
		token = token->next;
	}
	for(int i = 0; sh->heredoc_pipes[i]; i++)
	{
		close(sh->heredoc_pipes[i][1]);
	}
	return (1);
}
void	ft_get_heredoc(t_shell *sh, char *end, char	heredoc_index, bool quote)
{
	char	*prompt;
	prompt = NULL;
	char	*temp;
	close(sh->original_stdin);
	close(sh->original_stdout);
	ft_fprintf(2, "heredoc_index = %d\n", heredoc_index);
	for(int i = 0; sh->heredoc_pipes[i]; i++)
	{
		close(sh->heredoc_pipes[i][0]);

		if (i != heredoc_index)
		{
			close (sh->heredoc_pipes[i][1]);
		}
	}
	while (1)
	{
		prompt = readline("> ");
		if (ft_exit_status(0, 0, 0) == -1)
		{
			close(sh->heredoc_pipes[heredoc_index][1]);
			for(int i = 0; sh->heredoc_pipes[i]; i++)
				free(sh->heredoc_pipes[i]);
			free(sh->heredoc_pipes);
			free_tokens(sh->token);
			free(end);
			exit(130);
		}
		if (!prompt)
		{
			ft_fprintf(2, "warning: here-document delimited by end-of-file ");
			ft_fprintf(2, "(wanted '%s')\n", end);
			close(sh->heredoc_pipes[heredoc_index][1]);
			for(int i = 0; sh->heredoc_pipes[i]; i++)
				free(sh->heredoc_pipes[i]);
			free(sh->heredoc_pipes);
			free_tokens(sh->token);
			free(end);
			exit(0);
		}
		if (!*prompt)
		{
			free(prompt);
			continue ;
		}
		if (!ft_strncmp(prompt, end, ft_strlen(end) + 1) && prompt[0] != '\n')
		{
			close(sh->heredoc_pipes[heredoc_index][1]);
			for(int i = 0; sh->heredoc_pipes[i]; i++)
				free(sh->heredoc_pipes[i]);
			free(sh->heredoc_pipes);
			free(prompt);
			free_tokens(sh->token);
			free(end);
			exit(0);
		}
		if (prompt[0] && !quote)
		{
			temp = expand(prompt, sh, true);
			free(prompt);
			prompt = temp;
		}
		ft_putstr_fd(prompt, sh->heredoc_pipes[heredoc_index][1]);
		ft_putstr_fd("\n", sh->heredoc_pipes[heredoc_index][1]);
		free(prompt);
	}
}

