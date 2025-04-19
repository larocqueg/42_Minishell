/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:36:25 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/04/19 11:33:21 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_append_var(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
	{
		i++;
	}
	if (str[i] == '+')
		i++;
	if (str[i] == '=')
		return (1);
	else
		return (0);
}

void	create_var(char *var_name, char *var, t_shell *sh)
{
	char	*temp;
	char	*value;

	value = (ft_strjoin(var_name, "="));
	if (!value)
		return ;
	temp = ft_strjoin(value, var + ft_strlen_tochar(var, '=') + 1);
	if (!temp)
	{
		free(value);
		return ;
	}
	create_export(temp, sh);
	free(value);
	free(temp);
	free(var_name);
}

void	append_var(char *var_name, char *var, char *temp, t_shell *sh)
{
	char	*value;

	value = ft_strjoin(temp, var + ft_strlen_tochar(var, '=') + 1);
	if (!value)
		return ;
	temp = ft_strjoin(var_name, "=");
	if (!temp)
	{
		free(value);
		return ;
	}
	free(var_name);
	var_name = ft_strjoin(temp, value);
	if (!var_name)
		return ;
	create_export(var_name, sh);
	free(temp);
	free(value);
}

void	do_append(char *var, t_shell *sh)
{
	char	*temp;
	char	*var_name;

	var_name = ft_strndupmod(var, 0, ft_strlen_tochar(var, '+') - 1);
	if (!var_name)
		return ;
	temp = ft_get_env(var_name, sh->envp);
	if (!temp)
		create_var(var_name, var, sh);
	else
		append_var(var_name, var, temp, sh);
	free(var_name);
	ft_exit(0, 1, 0);
}

void	put_export(char *str)
{
	int		i;
	bool	equal;

	equal = false;
	i = 0;
	ft_printf("declare -x ");
	while (str[i])
	{
		if (str[i] == '=' && !equal)
		{
			equal = true;
			write(1, &str[i++], 1);
			write(1, "\"", 1);
		}
		else
			write(1, &str[i++], 1);
	}
	if (equal)
		write(1, "\"", 1);
	write(1, "\n", 1);
}
