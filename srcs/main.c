/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:06:52 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/19 11:58:16 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char *av[], char **envp)
{
	char	*prompt;
	char	pwd[1024];

	(void)ac;
	(void)av;
	(void)envp;

	getcwd(pwd, 1024);
	strcat(pwd, " < $ ");
	prompt = readline(pwd);
}
