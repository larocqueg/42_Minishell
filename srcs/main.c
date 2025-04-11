/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:44:47 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/11 21:12:45 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_env_size(char **envp);

void	ft_sh_init(t_shell *sh, char **envp)
{
	sh->original_stdin = dup(STDIN_FILENO);
	sh->original_stdout = dup(STDOUT_FILENO);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	sh->local_vars = NULL;
	sh->envp = clone_envp(envp);
	sh->env_size = get_env_size(sh->envp);
	sh->pipe_old = NULL;
	sh->pipe_new = NULL;
	sh->heredoc_pipes = NULL;
	sh->heredoc_count = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argv;
	if (argc > 1)
		return (0);
	ft_sh_init(&sh, envp);
	start_cli(&sh);
	free_envp(&sh);
	return (0);
}

static int	get_env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}
