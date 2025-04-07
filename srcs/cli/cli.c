/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:04:14 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/07 19:51:31 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	check_quotes(char *prompt)
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
		write(2, "minishell: syntax error: unclosed quotes\n", 41);
		ft_exit_status(2, true, false);
		return (0);
	}
	return (1);
}

int	check_tokens(t_token *token)
{
	int	token_count;
	t_token *temp;
	bool	pipe;
	temp = token;
	token_count = 0;

	while (temp)
	{
		pipe = false;
		if (token_count == 0 && token->type == PIPE)
		{
			ft_putstr_fd("minishell: syntax error: unexpected token '|'\n", 2);
			ft_exit_status(2, true, false);
			return (0);
		}
		if (temp->type != VAR && temp->type != WORD)
		{
			if (temp->type == PIPE)
				pipe = true;
			temp = temp -> next;
			token_count++;
			if (!temp)
			{
				ft_putstr_fd("minishell: syntax error: unexpected token '\\n'\n", 2);
				ft_exit_status(2, true, false);
				return (0);
			}
			else if ((temp->type == PIPE && pipe) || (temp->type != VAR && temp->type != WORD && !pipe))
			{
				ft_fprintf(2, "minishell: syntax error: unexpected token '%s'\n", token->token);
				ft_exit_status(2, true, false);
				return (0);
			}
		}
		temp = temp -> next;
		token_count++;
	}

	return (1);
}

int	check_syntax(t_token **token, char **prompt)
{
	char *temp;
	///t_token *temp;
	temp = *prompt;
	if (!check_quotes(temp))
		return 0;
	if (!check_tokens(*token))
		return (0);
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
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler); // re register signals
		dup2(sh->original_stdin, STDIN_FILENO);
		dup2(sh->original_stdout, STDOUT_FILENO);
		//dup2 will be inside cli_init();
		get_cli_pwd(sh);
		sh->heredoc_count = 0;
		//prompt = readline(sh->cli_text);
		prompt = readline("minishell $< ");
		if (!prompt)
		{
			printf("exit\n");
			ft_exit_status(0, true, true);
		}
		add_history(prompt);
		token = tokenize(prompt, sh);
		if (!check_syntax(&token, &prompt))
			continue;
		if (!get_heredoc(sh, token))
			continue;
		expand_tokens(token, sh);
		sh->heredoc_count = 0;
		create_cmds(sh, token);
		execute(sh);
		free(prompt);
		prompt = NULL;
		free(sh->cli_text);
	}
	close(sh->original_stdin);
	close(sh->original_stdout);
	rl_clear_history();

return 666;
}
