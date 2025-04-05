/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:44:47 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/05 13:31:19 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_env_size(char **envp);


int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;



	sh.DEBUG = 0;
	if (argc == 2 && argv[1][0] == '1')
		sh.DEBUG = 1;
	sh.original_stdin = dup(STDIN_FILENO);
	sh.original_stdout = dup(STDOUT_FILENO);
	sh.exit_code = 0;
	sh.local_vars = NULL;
	sh.envp = clone_envp(envp); // dar free em caso de exit ou ctrl + d
	sh.env_size = get_env_size(sh.envp);
	if (sh.DEBUG)
		printf("env size = %d\n", sh.env_size);
	sh.pipe_old = NULL;
	sh.pipe_new = NULL;
	sh.heredoc_count = 0;
	start_cli(&sh);
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
