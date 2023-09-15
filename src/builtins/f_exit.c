/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:10:39 by flauer            #+#    #+#             */
/*   Updated: 2023/09/15 10:53:53 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_exit(t_exec *cmd)
{
	int	code;

	code = 0;
	if (cmd->argv[1])
		code = ft_atoi(cmd->argv[1]);
	free_shell(cmd->sh);
	free_exec(cmd);
	wait_exit();
	exit(code);
}

void	f_exit2(t_shell *sh, char *msg, int code)
{
	free_shell(sh);
	printf("%s\n", msg);
	exit(code);
}
