/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:04:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/26 20:30:04 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cmd_addback(t_cmd **cmd, t_cmd *new_cmd)
{
	t_cmd	*temp;

	if (!new_cmd)
		return ;
	if (!*cmd)
	{
		*cmd = new_cmd;
		return ;
	}
	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	temp->next = new_cmd;
}


char **append_cmd(char **cmd, char *newcmd)
{
	int	i;
	char **result;

	i = 0;
	if (!cmd)
	{
		cmd = malloc(sizeof(char *) * 2);
		cmd[0] =  ft_strdup(newcmd);
		cmd[1] = NULL;
		return (cmd);
	}
	while(cmd[i] != NULL)
		i++;
	result = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while(cmd[i])
	{
		result[i] = ft_strdup(cmd[i]);
		i++;
	}
	result[i++] = ft_strdup(newcmd);
	result[i] = NULL;
	free(cmd);
	return (result);
}

void	extract_cmd(t_cmd **cmd, t_token **token, bool from_pipe)
{
	t_cmd *newcmd = malloc(sizeof(t_cmd));
	newcmd -> fd_out = -1;
	newcmd -> fd_in = -1;
	newcmd -> next = NULL;
	newcmd -> cmd = NULL;
	newcmd->to_pipe = false;
	newcmd->from_pipe = false;
	while (*token && (*token)->type != PIPE)
	{
		if (from_pipe)
			newcmd -> from_pipe = true;
		if ((*token) -> type == TOFILE)
		{
			(*token) = (*token) -> next;
			newcmd -> fd_out = open((*token)->token, O_RDWR | O_TRUNC | O_CREAT, 0644);
		}
		else if ((*token) -> type == INFILE)
		{
			(*token) = (*token) -> next;
			newcmd -> fd_in = open((*token)->token, O_RDONLY);
		}
		else if ((*token) -> type == APPEND)
		{
			(*token) = (*token) -> next;
			newcmd -> fd_out = open((*token)->token, O_RDWR | O_APPEND | O_CREAT, 0644);
		}
		else if ((*token) -> type == HERE_DOC)
		{
			//newcmd -> fd_out = open(), O_RDWR | O_APPEND);
		}
		else if ((*token) -> type == WORD)
		{
			newcmd->cmd = append_cmd(newcmd->cmd, (*token)->token);
		}
		(*token) = (*token) -> next;
	}
	if ((*token) && (*token) -> type == PIPE)
		newcmd -> to_pipe = true;
	ft_cmd_addback(cmd, newcmd);
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
		t_cmd *cmds;

		bool from_pipe = false;
		cmds = NULL;
		while (token)
		{
			if (token->type == PIPE)
			{
				from_pipe = true;
				token = token -> next;
			}
			extract_cmd(&cmds, &token, from_pipe);
			//ft_printf("token = %s type = %d\n", token->token, token->type);
		}
		while(cmds)
		{
			printf("-----------------------\n");
			for(int i = 0; cmds->cmd[i]; i++)
				printf("%s ", cmds->cmd[i]);
			printf("\nfdin %d\n", cmds->fd_in);
			printf("fdout %d\n", cmds->fd_out);
			printf("topipe  "); cmds->to_pipe ? printf("true\n") : printf("false\n");
			printf("frompipe  "); cmds->from_pipe ? printf("true\n") : printf("false\n");
			cmds = cmds->next;
		}
	}
}

