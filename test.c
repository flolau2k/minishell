/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:26:59 by flauer            #+#    #+#             */
/*   Updated: 2023/08/31 09:39:25 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	init(t_shell *sh, int argc, char **argv, char **env)
{
	if (argc > 2)
		ft_error("put your args as one string please!", GENERAL_ERROR);
	*sh = (t_shell){};
	if (argc == 2)
		sh->line = argv[1];
	sh->env = set_env(env, NULL);
	return (true);
}
