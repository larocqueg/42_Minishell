/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:04:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/09 16:30:08 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_eof_close(t_shell *sh)
{
	ft_fprintf(1, "exit\n");
	close(sh->original_stdin);
	close(sh->original_stdout);
	rl_clear_history();
	ft_exit_status(0, false, true);
}

int	start_cli(t_shell *sh)
{
	t_cmd *cmd;
	cmd = sh->cmd;
	while (1)
	{
		sh->prompt = readline("minishell $< ");
		if (!sh->prompt)
			ft_eof_close(sh);
		add_history(sh->prompt);
		if (!tokenize(sh->prompt, sh))
			continue;
		if (!check_syntax(sh))
			continue;
		if (!get_heredoc(sh))
			continue;
		if (!expand_tokens(sh))
			continue;
		create_cmds(sh);
		execute(sh);
	}
}
