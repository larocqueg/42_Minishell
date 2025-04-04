/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 20:23:54 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/04 20:49:54 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_signal_handler(int sig)
{

	if (sig == SIGINT)
	{
		return ;
	}
	else if (sig == SIGQUIT)
	{
		ft_printf("Quit (Core Dumped)\n");
		return ;
	}
	else if (sig == SIGPIPE)
	{
		//nao sei oq tem q fazer aqui;
	}
}
