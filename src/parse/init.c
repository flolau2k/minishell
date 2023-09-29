/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:26:59 by flauer            #+#    #+#             */
/*   Updated: 2023/09/29 16:23:43 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	init(t_shell *sh, int argc, char **argv, char **env)
{
	(void) argv;
	if (argc > 1)
		ft_error(NULL, "This program does not take args!", GENERAL_ERROR);
	*sh = (t_shell){};
	sh->env = copy_env(env);
	sh->ttyin = dup(STDIN_FILENO);
	sh->ttyout = dup(STDOUT_FILENO);
	return (true);
}
