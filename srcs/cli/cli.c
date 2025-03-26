/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:04:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/26 18:42:00 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	extract_cmd(t_cmd *cmd, t_token *token, bool to_pipe)
{
	int fdin = STDIN_FILENO;
	int fdout = STDOUT_FILENO;
	while (token)
	{
		if (token->type == | && cmd->fd_out == STDOUT_FILENO)
		{
			fd_out = pipe_new[1];
			to_pipe = true;
		}
		else if (token->type == >)
		{
			if (to_pipe == true)
			{
				cmd_in = old_pipe[1];
			}
			cmd -> fd_out > file_fd;
		}
		else if (token->type == >>)
		{
		}
		else if (token->type == <)
		{
		}
		else if (token->type == <<)
		{
		}
		else
			cmd[i++] = token->token;
		cmd -> fdout = fdout;
		token = token->next;
	}
}


int	start_cli(t_shell *sh)
{
	t_token	*token;
	char	*prompt;

	token = NULL;
	while (1)
	{
		get_cli_pwd(sh);
		prompt = readline(sh->cli_text);
		free(sh->cli_text);
		token = tokenize(prompt);
		expand_tokens(token);
		while (token)
		{
			ft_printf("token = %s type = %d\n", token->token, token->type);
			token = token->next;
		}
	}
}
			sh -> pipe[i].in = pipe()
			pipeold[2]
			pipenew pipe = pipenew
			if fdout = pipe
				pipenew = pipe()
				dup2(STDOUT, pipenew[1])
			dup2(STDIN, pipeold[0])
