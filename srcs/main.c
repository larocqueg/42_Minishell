/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:44:47 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/27 17:37:05 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_code;

int	main(int argc, char **argv, char **envp)
{
	t_shell	sh;

	exit_code = 2;
	sh.envp = envp;
	sh.pipe_old = NULL;
	sh.pipe_new = NULL;
	start_cli(&sh);
	return (0);
}

