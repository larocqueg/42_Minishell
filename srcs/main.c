/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:44:47 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/09 15:44:45 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_env_size(char **envp);

void	ft_sh_init(t_shell *sh, char **envp)
{
	sh->DEBUG = 0;
	sh->original_stdin = dup(STDIN_FILENO);
	sh->original_stdout = dup(STDOUT_FILENO);
	sh->exit_code = 0;
	sh->local_vars = NULL;
	sh->envp = clone_envp(envp);
	sh->env_size = get_env_size(sh->envp);
	sh->pipe_old = NULL;
	sh->pipe_new = NULL;
	sh->heredoc_count = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;
	(void)argv;
	//if (argc > 1)
		//return ;
	ft_sh_init(&sh, envp);
	if (argc == 2)
		sh.DEBUG = 1;
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
