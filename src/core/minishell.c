/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 15:47:17 by pcazac           ###   ########.fr       */
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
		// free root tree;
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
