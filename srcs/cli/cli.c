/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:04:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/30 16:22:05 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//dup2 will be inside cli_init();

static int	ft_close_clear(t_shell *sh)
{
	close(sh->original_stdin);
	close(sh->original_stdout);
	rl_clear_history();
	return (1);
}

int	start_cli(t_shell *sh)
{
	char	*prompt;
	t_token	*token;

	token = NULL;
	while (1)
	{
		dup2(sh->original_stdin, STDIN_FILENO);
		dup2(sh->original_stdout, STDOUT_FILENO);
		get_cli_pwd(sh);
		prompt = readline(sh->cli_text);
		if (prompt)
		{
			add_history(prompt);
			token = tokenize(prompt, sh);
			expand_tokens(token);
			create_cmds(sh, token);
			execute(sh);
			free(prompt);
			prompt = NULL;
		}
		free(sh->cli_text);
	}
	return (ft_close_clear(sh));
}
