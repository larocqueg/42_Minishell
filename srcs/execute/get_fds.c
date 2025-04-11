/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:48:23 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/11 17:49:15 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*getfd_tofile(t_token *token, t_cmd *newcmd)
{
	token = token -> next;
	if (newcmd -> fd_out != -1)
		close(newcmd->fd_out);
	newcmd -> fd_out = open(token->token, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (newcmd -> fd_out == -1)
		newcmd->tofile_error = true;
	return (token);
}

t_token	*getfd_infile(t_token *token, t_cmd *newcmd)
{
	token = token -> next;
	if (newcmd -> fd_in != -1 && !newcmd->heredoc)
		close(newcmd->fd_in);
	newcmd -> fd_in = open(token->token, O_RDONLY);
	if (newcmd -> fd_in == -1)
		newcmd->infile_error = true;
	newcmd->heredoc = false;
	return (token);
}

t_token	*getfd_append(t_token *token, t_cmd *newcmd)
{
	token = token -> next;
	if (newcmd -> fd_out != -1)
		close(newcmd->fd_out);
	newcmd -> fd_out = open(token->token, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (newcmd -> fd_out == -1)
		newcmd->tofile_error = true;
	return (token);
}

t_token	*getfd_heredoc(t_token *token, t_cmd *newcmd, t_shell *sh)
{
	token = token -> next;
	if (newcmd -> fd_in != -1 && !newcmd->heredoc)
		close(newcmd->fd_in);
	newcmd -> fd_in = sh->heredoc_pipes[sh->heredoc_count][0];
	sh->heredoc_count++;
	newcmd->heredoc = true;
	return (token);
}

t_token	*get_command(t_token *token, t_cmd *newcmd)
{
	if ((token->type == WORD) && token->token)
		newcmd->cmd = append_cmd(newcmd->cmd, token->token);
	return (token);
}
