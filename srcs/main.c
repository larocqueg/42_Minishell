/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:44:47 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/28 10:02:29 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;


	sh.DEBUG = 0;
	if (argc == 2)
		sh.DEBUG = 1;
	g_exit_code = 2;
	sh.envp = envp;
	sh.pipe_old = NULL;
	sh.pipe_new = NULL;
	start_cli(&sh);
	return (0);
}

