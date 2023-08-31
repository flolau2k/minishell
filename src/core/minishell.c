/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/08/31 14:46:46 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	main_loop(t_shell *sh)
{
	t_cmd	*root;

	if (sh->line)
	{
		root = do_lexing(sh);
		printf("<<<------###TREE ROOT###----->>>\n\n");
		print_tree(&root);
		do_parsing(root);
		printf("\n\n");
		printf("<<<------###PARSED AST TREE###----->>>\n\n");
		print_tree(&root);
		execute(root);
	}
	while (true)
	{
		sh->line = readline(MINISHELL_PROMPT);
		root = do_lexing(sh);
		execute(root);
		free(sh->line);
		// free root tree;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	sh;

	init(&sh, argc, argv, env);
	// signal_handler(); // handle signals
	main_loop(&sh);
	// cleanup(&sh);
	return (EXIT_SUCCESS);
}
