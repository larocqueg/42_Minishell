/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:04:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/30 15:35:31 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	start_cli(t_shell *sh)
{
	t_token	*token;
	char	*prompt;
	t_cmd *cmd;

	cmd = sh->cmd;
	token = NULL;
	while (1)
	{
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
			dup2(sh->original_stdin, STDIN_FILENO);
			dup2(sh->original_stdout, STDOUT_FILENO);
			prompt = NULL;
		}
		free(sh->cli_text);
	}
	close(sh->original_stdin);
	close(sh->original_stdout);
	rl_clear_history();

return 666;
}
