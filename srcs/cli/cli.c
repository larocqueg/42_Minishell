/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:04:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/17 22:23:43 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_eof_close(t_shell *sh)
{
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_fprintf(2, "exit\n");
	close(sh->original_stdin);
	close(sh->original_stdout);
	free_envp(sh);
	rl_clear_history();
	if (sh->heredoc_count > 0)
		free(sh->heredoc_pipes);
	ft_exit_status(0, false, true);
}

void	reset_cli(t_shell *sh)
{
	dup2(sh->original_stdin, STDIN_FILENO);
	dup2(sh->original_stdout, STDOUT_FILENO);
	signal_default();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	sh->heredoc_count = 0;
}

int	start_cli(t_shell *sh)
{
	while (1)
	{
		sh->prompt = readline("minishell $< ");
		if (!sh->prompt)
			ft_eof_close(sh);
		if (!*sh->prompt)
			continue ;
		add_history(sh->prompt);
		if (!tokenize(sh->prompt, sh))
			continue ;
		if (!check_syntax(sh))
			continue ;
		if (!get_heredoc(sh))
			continue ;
		expand_tokens(sh);
		if (!create_cmds(sh))
			continue ;
		execute(sh);
		reset_cli(sh);
		if (!isatty(STDIN_FILENO) && !isatty(STDOUT_FILENO))
			ft_eof_close(sh);
	}
	exit(0);
}
