/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 16:03:03 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/10 20:55:11 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_quotes(char c, bool *in_single_quotes, bool *in_quotes)
{
	if (c == 39 && !*in_quotes)
	{
		if (*in_single_quotes)
			*in_single_quotes = false;
		else
			*in_single_quotes = true;
	}
	else if (c == 34 && !*in_single_quotes)
	{
		if (*in_quotes)
			*in_quotes = false;
		else
			*in_quotes = true;
	}
}

char	ft_ischar(int *i)
{
	(*i)++;
	return ('\0');
}

char	*remove_quotes(char *str)
{
	char	quote;
	char	*result;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == '\0')
			quote = str[i++];
		else if (str[i] == quote)
			quote = ft_ischar(&i);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

char	*extract_variable(char *str, int i)
{
	int	j;

	j = i;
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	if (j >= i)
		return (ft_strndupmod(str, i, --j));
	return (NULL);
}

int	ft_is_all_var(char	*str)
{
	int	i;

	i = 1;
	if (str[0] != '$')
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (!str[i])
		return (1);
	else
		return (0);
}

char	*ft_expand_string(char *str, size_t *i, t_shell *sh)
{
	char	*variable_name;
	char	*temp;
	char	*content;

	temp = NULL;
	variable_name = extract_variable(str, *i);
	if (!variable_name)
		return (free(str), NULL);
	content = ft_get_env(variable_name, sh->envp);
	free(variable_name);
	if (!content && ft_is_all_var(str))
		return (free(str), NULL);
	temp = ft_insertstr(str, (*i)--, content);
	free(str);
	str = temp;
	if (content)
	{
		(*i) += ft_strlen(content) - 1;
	}
	return (str);
}

char	*ft_expand_exit(char	*str, size_t *i)
{
	char	*temp;
	char	*exit_code;

	exit_code = ft_itoa(ft_exit_status(0, 0, 0));
	if (!exit_code)
	{
		free(str);
		return (NULL);
	}
	temp = ft_insertstr(str, (*i)--, exit_code);
	(*i) += ft_strlen(exit_code);
	free(exit_code);
	free(str);
	return (temp);
}

char	*ft_expand_vars(char *str, size_t *i, t_shell *sh)
{
	if (str[*i] && str[*i] == '?')
		str = ft_expand_exit(str, i);
	else if (ft_isalnum(str[*i]) || str[*i] == '_')
		str = ft_expand_string(str, i, sh);
	return (str);
}

char	*expand(char *str, t_shell *sh, bool heredoc)
{
	size_t	i;
	char	*result;
	bool	in_quotes;
	bool	in_single_quotes;

	in_single_quotes = false;
	in_quotes = false;
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		set_quotes(result[i], &in_single_quotes, &in_quotes);
		if (result[i] == '$' && (!in_single_quotes || heredoc))
		{
			i++;
			if (result[i] == '?' || ft_isalpha(result[i]) || result[i] == '_' )
				result = ft_expand_vars(result, &i, sh);
			if (!result)
				return (NULL);
		}
		i++;
	}
	return (result);
}

void	expand_tokens(t_shell *sh)
{
	char	*temp;
	t_token	*token;

	temp = NULL;
	token = sh->token;
	while (token)
	{
		if (token->type == WORD)
		{
			temp = expand(token->token, sh, false);
			free(token->token);
			token->token = remove_quotes(temp);
			free(temp);
		}
		token = token -> next;
	}
}
