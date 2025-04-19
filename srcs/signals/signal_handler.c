/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:23:54 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/18 16:14:19 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_exit_status(130, true, false);
	}
}

void	ft_heredoc_child_signal_handler(int sig)
{
	ft_exit_status(-1, true, false);
	close(STDIN_FILENO);
}

void	ft_heredoc_parent_signal_handler(int sig)
{
	write(1, "\n", 1);
}

void	child_signal_handler(int sig)
{
	if (sig == SIGPIPE)
	{
		ft_exit_status(141, 1, 0);
	}
}

void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
