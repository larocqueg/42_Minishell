/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:04:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/03 21:39:30 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	check_quotes(char *prompt, t_shell *sh)
{
	int	quote;
	int	i;

	quote = '\0';
	i = 0;
	while (prompt[i])
	{
		if ((prompt[i] == '\"'|| prompt[i] == '\''))
		{
			if (!quote)
				quote = prompt[i];
			else if (prompt[i] == quote)
				quote = '\0';
		}
		i++;
	}
	if (quote != '\0')
	{
		write(2, "minishell: Syntax error: unclosed quotes\n", 41);
		sh -> exit_code = 2;
		return (0);
	}
	return (1);
}
int	check_tokens(t_token *token, t_shell *sh)
{

	
}

int	check_syntax(t_token **token, char **prompt, t_shell *sh)
{
	char *temp;
	///t_token *temp;
	temp = *prompt;
	if (!check_quotes(temp, sh))
		return 0;
	if (!check_tokens(*token, sh))
	return (1);
}

int	start_cli(t_shell *sh)
{
	t_token	*token;
	char	*prompt;
	t_cmd *cmd;

	cmd = sh->cmd;
	token = NULL;
	while (1)
	{
		dup2(sh->original_stdin, STDIN_FILENO);
		dup2(sh->original_stdout, STDOUT_FILENO);
		//dup2 will be inside cli_init();
		get_cli_pwd(sh);
		sh->heredoc_count = 0;
		//prompt = readline(sh->cli_text);
		prompt = readline("minishell $< ");
		if (prompt)
		{
			add_history(prompt);
			token = tokenize(prompt, sh);
			if (!check_syntax(&token, &prompt, sh))
				continue;
			get_heredoc(sh, token);
			expand_tokens(token, sh);
			create_cmds(sh, token);
			execute(sh);
			free(prompt);
			prompt = NULL;
		}
		free(sh->cli_text);
	}
	close(sh->original_stdin);
	close(sh->original_stdout);
	rl_clear_history();

return 666;
}
