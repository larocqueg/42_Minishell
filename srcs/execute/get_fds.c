/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:48:23 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/18 21:32:39 by rafaelfe         ###   ########.fr       */
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

int ft_match(char *str, char *line)
{
	if (!*str && !*line)
		return (1);
	if (*str == '*')
	{
		if (ft_match(str + 1, line))
			return (1);
		if (*line && ft_match(str, line + 1))
			return (1);
	}
	else if (*str == *line)
		return (ft_match(str + 1, line + 1));
	return (0);
}


char *get_dir(DIR *directory)
{
	struct dirent *entry;

	char	*line;
	entry = readdir(directory);
	if (!entry)
		return (NULL);
	line = entry->d_name;
	if (!line)
		return (NULL);
	return (line);
}
char *get_arg(DIR *directory, char *str)
{
	char *line;
	while (1)
	{
		line = get_dir(directory);
		if (!line)
			return (NULL);
		if (ft_match(str, line))
			return (line);
	}
}
t_token	*get_command(t_token *token, t_cmd *newcmd)
{
	char *line;
	static DIR *directory;
	line = NULL;
	if ((token->type == WORD || token->type == WILDCARD) && token->token)
	{
		if (token->type == WILDCARD)
		{
			directory = opendir(".");
			while (1)
			{
				line = get_arg(directory, token->token);
				if (!line)
					break;
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
