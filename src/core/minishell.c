/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 13:30:44 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	main_loop(t_shell *sh)
{
	t_cmd	*root;

	if (sh->line)
	{
		root = parse(sh->line);
		execute(root);
	}
	while (true)
	{
		sh->line = readline(MINISHELL_PROMPT);
		root = parse(sh->line);
		execute(root);
		free(sh->line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	sh;

	init(&sh, argc, argv, env);
	signal_handler(); // handle signals
	main_loop(&sh);
	cleanup(&sh);
	return (EXIT_SUCCESS);
}
