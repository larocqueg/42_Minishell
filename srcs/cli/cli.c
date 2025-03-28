/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:04:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/28 22:49:23 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	start_cli(t_shell *sh)
{
	t_token	*token;
	char	*prompt;
	int status;
	t_cmd *cmd;

	cmd = sh->cmd;
	token = NULL;
	while (1)
	{
		get_cli_pwd(sh);
		prompt = readline(sh->cli_text);
		add_history(prompt);
		free(sh->cli_text);
		token = tokenize(prompt);
		expand_tokens(token);
		create_cmds(sh, token);
	// 	while(sh->cmd)
	// {
	// 	printf("-----------------------\n");
	// 	for(int i = 0; sh->cmd->cmd[i]; i++)
	// 		printf("%s ", sh->cmd->cmd[i]);
	// 	printf("\nfdin %d\n", sh->cmd->fd_in);
	// 	printf("fdout %d\n", sh->cmd->fd_out);
	// 	printf("topipe  "); sh->cmd->to_pipe ? printf("true\n") : printf("false\n");
	// 	printf("frompipe  "); sh->cmd->from_pipe ? printf("true\n") : printf("false\n");
	// 	sh->cmd = sh->cmd->next;
	// }
		execute(sh);
	}

	rl_clear_history();

return 666;
}
