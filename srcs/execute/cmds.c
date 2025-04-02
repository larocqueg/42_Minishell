/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:44:32 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/02 17:35:44 by rafaelfe         ###   ########.fr       */
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
		cmd = malloc(sizeof(char **) * 2);
		cmd[0] =  ft_strdup(newcmd);
		cmd[1] = NULL;
		return (cmd);
	}
	while(cmd[i] != NULL)
		i++;
	result = malloc(sizeof(char **) * (i + 2));
	i = 0;
	while(cmd[i])
	{
		result[i] = cmd[i];
		i++;
	}
	result[i++] = ft_strdup(newcmd);
	result[i] = NULL;
	free(cmd);
	return (result);
}

void	extract_cmd(t_cmd **cmd, t_token **token, bool from_pipe, t_shell *sh)
{
	t_cmd *newcmd = malloc(sizeof(t_cmd));
	t_token *temp = *token;
	newcmd -> fd_out = -1;
	newcmd -> fd_in = -1;
	newcmd -> next = NULL;
	newcmd -> cmd = NULL;
	newcmd->to_pipe = false;
	newcmd->from_pipe = false;
	bool	hascmd = false;
	int heredoc_count = 0;
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
			(*token) = (*token) -> next;
			newcmd -> fd_in = sh->heredoc_pipes[heredoc_count][0];
			heredoc_count++;
		}
		else if ((*token) -> type == WORD || (*token)->type == VAR)
		{
			if ((*token)->type == WORD)
				newcmd->cmd = append_cmd(newcmd->cmd, (*token)->token);
			else if ((*token) -> type == VAR)
			{
				while(temp && temp->type == VAR)
				{
					if (temp->type != VAR)
					{
						if (temp->type != WORD && temp->type != VAR)
							break;
						hascmd = true;
						break;
					}
					temp = temp->next;
				}
			if ((*token)->type == VAR && !hascmd)
				newcmd->cmd = append_cmd(newcmd->cmd, (*token)->token);
			}

		}
		if (*token)
			(*token) = (*token) -> next;
	}
	hascmd = false;
	if ((*token) && (*token) -> type == PIPE)
		newcmd -> to_pipe = true;
	ft_cmd_addback(cmd, newcmd);
}

void	create_cmds(t_shell *sh, t_token *token)
{
	bool from_pipe = false;
	sh->cmd = NULL;
	while (token)
	{
		if (token->type == PIPE)
		{
			from_pipe = true;
			token = token -> next;
		}
		extract_cmd(&sh->cmd, &token, from_pipe, sh);
	}

	if (!sh->DEBUG)
		return;
	t_cmd *cmd = sh->cmd;
	 while(cmd)
	 {
		printf("-------CMDS---------\n");
	 	for(int i = 0; cmd->cmd[i]; i++)
			printf("%s ", cmd->cmd[i]);
		printf("\nfdin %d\n", cmd->fd_in);
	 	printf("fdout %d\n", cmd->fd_out);
	 	printf("topipe  "); cmd->to_pipe ? printf("true\n") : printf("false\n");
	 	printf("frompipe  "); cmd->from_pipe ? printf("true\n") : printf("false\n");
	 	cmd = cmd->next;
	 }
	printf("---------END CMDS--------\n");
}
