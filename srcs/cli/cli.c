/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:04:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/03/21 11:46:52 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	start_cli(t_shell *sh)
{
	t_token	*token;
	char	*prompt;

	while (1)
	{
		get_cli_pwd(sh);
		prompt = readline(sh->cli_text);
		free(sh->cli_text);
		token = tokenize(prompt);
		while (token)
		{
			ft_printf("token = %s type =%d\n", token->token, token->type);
			token = token->next;
		}
	}
}
