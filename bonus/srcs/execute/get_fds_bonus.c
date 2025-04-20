/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:45:26 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/20 18:45:28 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

t_token	*getfd_tofile(t_token *token, t_cmd *newcmd)
{
	token = token -> next;
	if (token->wildcard)
		newcmd->tofile_error = true;
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
	if (token->wildcard)
		newcmd->infile_error = true;
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
	if (token->wildcard)
		newcmd->tofile_error = true;
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
	char		*line;
	static DIR	*directory;

	line = NULL;
	if ((token->type == WORD) && token->token)
	{
		if (token->wildcard)
		{
			directory = opendir(".");
			while (1)
			{
				line = get_arg(directory, token->token);
				if (!line)
					break ;
				newcmd->cmd = append_cmd(newcmd->cmd, line);
				line = NULL;
			}
			closedir(directory);
		}
		else
		{
			newcmd->cmd = append_cmd(newcmd->cmd, token->token);
		}
	}
	return (token);
}
