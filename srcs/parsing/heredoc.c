/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:23:45 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/05 22:45:51 by rafaelfe         ###   ########.fr       */
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
			ft_fprintf(2, "warning: here-document at line 1 delimited by end-of-file ");
			ft_fprintf(2, "(wanted '%s')\n", end);
			close(sh->heredoc_pipes[i][1]);
			break; //exit(0); only if fork!
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
void heredoc_signal_handler(int sig)
{
	if (sig)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
		ft_exit_status(130, true, true);
	}
}

int	get_heredoc(t_shell *sh, t_token *token)
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
	temp = token;
	ft_heredoc_init(sh);
	pid = fork();
	if (pid == 0)
	{
		signal_default();
		signal(SIGINT, heredoc_signal_handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGPIPE, SIG_IGN);


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
		ft_exit_status(0, 1, 1);
	}
	else
		waitpid(pid, &status, 0);

	if (WEXITSTATUS(status) == 130)
	{

		return (0);
	}
	else
	{
		for (int i = 0; i < sh->heredoc_count; i++)
			close(sh->heredoc_pipes[0][1]);
		ft_fprintf(2, "exit code is: %d\n", WEXITSTATUS(status));
		return (1);

	}
}
