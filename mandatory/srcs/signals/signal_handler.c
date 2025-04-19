/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:23:54 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/19 11:36:07 by rafaelfe         ###   ########.fr       */
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
		ft_exit(130, true, false);
	}
}

void	ft_heredoc_child_signal_handler(int sig)
{
	(void)sig;
	ft_exit(-1, true, false);
	close(STDIN_FILENO);
}

void	ft_heredoc_parent_signal_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	child_signal_handler(int sig)
{
	if (sig == SIGPIPE)
		ft_exit(141, 1, 0);
}

void	signal_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
