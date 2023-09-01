/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:39 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 16:49:11 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_exit(t_exec *cmd)
{
	int	code;

	code = 0;
	if (cmd->argv[1])
		code = ft_atoi(cmd->argv[1]);
	exit(code);
}
