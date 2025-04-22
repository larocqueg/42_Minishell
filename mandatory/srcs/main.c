/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:44:47 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/21 16:11:08 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	(void)argv;
	if (argc != 1 /*|| !isatty(STDOUT_FILENO)*/)
		return (1);
	ft_sh_init(&sh, envp);
	ft_get_shlvl(&sh);
	ft_init_pwd(&sh);
	start_cli(&sh);
	free_envp(&sh);
	return (0);
}

void	ft_sh_init(t_shell *sh, char **envp)
{
	sh->pids = NULL;
	sh->original_stdin = dup(STDIN_FILENO);
	sh->original_stdout = dup(STDOUT_FILENO);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	signal(SIGPIPE, SIG_IGN);
	sh->local_vars = NULL;
	sh->env_size = 0;
	sh->envp = clone_envp(sh, envp);
	sh->pipe_old = NULL;
	sh->pipe_new = NULL;
	sh->heredoc_pipes = NULL;
	sh->heredoc_count = 0;
}

void	ft_get_shlvl(t_shell *sh)
{
	long long	shlvl;
	char		*temp;
	char		*itoa;

	temp = ft_get_env("SHLVL", sh->envp);
	if (!temp)
	{
		create_export("SHLVL=1", sh);
		return ;
	}
	shlvl = ft_atoll(temp);
	if (shlvl < 0)
		shlvl = 0;
	else if (shlvl > 1000)
		shlvl = 0;
	itoa = ft_itoa(shlvl + 1);
	temp = ft_strjoin("SHLVL=", itoa);
	create_export(temp, sh);
	free(temp);
	free(itoa);
}

void	ft_init_pwd(t_shell *sh)
{
	char	*current_pwd;
	char	*temp;

	temp = ft_get_env("OLDPWD", sh->envp);
	if (!temp)
		create_export("OLDPWD=", sh);
	temp = NULL;
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return ;
	temp = ft_strjoin("PWD=", current_pwd);
	create_export(temp, sh);
	free(current_pwd);
	free (temp);
}
