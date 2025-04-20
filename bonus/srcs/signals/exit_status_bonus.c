/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-la-r <gde-la-r@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 18:49:13 by gde-la-r          #+#    #+#             */
/*   Updated: 2025/04/20 18:49:14 by gde-la-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	ft_exit(int exit_code, bool set, bool close)
{
	static int	exit_status;

	if (set)
		exit_status = exit_code;
	if (close)
		exit (exit_status);
	return (exit_status);
}
