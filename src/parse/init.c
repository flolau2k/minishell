/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:26:59 by flauer            #+#    #+#             */
/*   Updated: 2023/09/05 16:08:32 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	init(t_shell *sh, int argc, char **argv, char **env)
{
	if (argc > 2)
		ft_error("put your args as one string please!", GENERAL_ERROR);
	*sh = (t_shell){};
	if (argc == 2)
		sh->line = argv[1];
	sh->env = copy_env(env);
	sh->ttyin = dup(STDIN_FILENO);
	sh->ttyout = dup(STDOUT_FILENO);
	return (true);
}

