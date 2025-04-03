/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:04:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/03 18:29:02 by rafaelfe         ###   ########.fr       */
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
		dup2(sh->original_stdin, STDIN_FILENO);
		dup2(sh->original_stdout, STDOUT_FILENO);
		//dup2 will be inside cli_init();
		get_cli_pwd(sh);
		sh->heredoc_count = 0;
		//prompt = readline(sh->cli_text);
		prompt = readline("minishell $< ");
		if (prompt)
		{
			add_history(prompt);
			token = tokenize(prompt, sh);
			get_heredoc(sh, token);
			expand_tokens(token, sh);
			create_cmds(sh, token);
			execute(sh);
			free(prompt);
			prompt = NULL;
		}
		free(sh->cli_text);
	}
	close(sh->original_stdin);
	close(sh->original_stdout);
	rl_clear_history();

return 666;
}
