/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:04:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/27 22:14:08 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	start_cli(t_shell *sh)
{
	t_token	*token;
	char	*prompt;
	int		pid;
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
		pid = fork();
		if (pid != 0)
		 	waitpid(pid, &status, 0);
		else if (pid == 0)
		{
			token = tokenize(prompt);
			expand_tokens(token);
			create_cmds(sh, token);
			cmd = sh->cmd;
		while(cmd)
		{
			printf("-----------------------\n");
			for(int i = 0; cmd->cmd[i]; i++)
				printf("%s ", cmd->cmd[i]);
			printf("\nfdin %d\n", cmd->fd_in);
			printf("fdout %d\n", cmd->fd_out);
			printf("topipe  "); cmd->to_pipe ? printf("true\n") : printf("false\n");
			printf("frompipe  "); cmd->from_pipe ? printf("true\n") : printf("false\n");
			cmd = cmd->next;
		}
			execute(sh);
		}
		free(prompt);
	}
return 666;
}

