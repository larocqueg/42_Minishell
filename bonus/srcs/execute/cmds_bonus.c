/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:39:27 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/18 21:32:09 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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

char	**append_cmd(char **cmd, char *newcmd)
{
	int		i;
	char	**result;

	i = 0;
	if (!cmd)
	{
		cmd = malloc(sizeof(char **) * 2);
		cmd[0] = ft_strdup(newcmd);
		cmd[1] = NULL;
		return (cmd);
	}
	while (cmd[i] != NULL)
		i++;
	result = malloc(sizeof(char **) * (i + 2));
	i = 0;
	while (cmd[i])
	{
		result[i] = cmd[i];
		i++;
	}
	result[i++] = ft_strdup(newcmd);
	result[i] = NULL;
	free(cmd);
	return (result);
}

t_cmd	*cmd_init(bool from_pipe)
{
	t_cmd	*newcmd;

	newcmd = malloc(sizeof(t_cmd));
	if (!newcmd)
		return (NULL);
	newcmd -> fd_out = -1;
	newcmd -> fd_in = -1;
	newcmd -> next = NULL;
	newcmd -> cmd = NULL;
	newcmd->to_pipe = false;
	newcmd->from_pipe = from_pipe;
	newcmd->infile_error = false;
	newcmd->tofile_error = false;
	newcmd->heredoc = false;
	return (newcmd);
}

int	extract_cmd(t_cmd **cmd, t_token **token, bool from_pipe, t_shell *sh)
{
	t_cmd	*newcmd;

	newcmd = cmd_init(from_pipe);
	if (!newcmd)
		return (0);
	while (*token && (*token)->type != PIPE)
	{
		if ((*token)-> type == TOFILE && !perm_error(newcmd))
			(*token) = getfd_tofile(*token, newcmd);
		else if ((*token)-> type == INFILE && !perm_error(newcmd))
			(*token) = getfd_infile(*token, newcmd);
		else if ((*token)-> type == APPEND && !perm_error(newcmd))
			(*token) = getfd_append(*token, newcmd);
		else if ((*token)-> type == HERE_DOC && !perm_error(newcmd))
			(*token) = getfd_heredoc(*token, newcmd, sh);
		else if ((*token)-> type == WORD || (*token)->type == WILDCARD)
			(*token) = get_command(*token, newcmd);
		if (*token)
			(*token) = (*token)-> next;
	}
	if ((*token) && (*token)-> type == PIPE)
		newcmd -> to_pipe = true;
	ft_cmd_addback(cmd, newcmd);
	return (1);
}

int	create_cmds(t_shell *sh)
{
	t_token	*token;
	bool	from_pipe;

	sh->heredoc_count = 0;
	token = sh->token;
	from_pipe = false;
	sh->cmd = NULL;
	while (token)
	{
		if (token->type == PIPE)
		{
			from_pipe = true;
			token = token -> next;
		}
		if (!extract_cmd(&sh->cmd, &token, from_pipe, sh))
		{
			ft_free_until_cmds(sh);
			return (0);
		}
	}
	return (1);
}
