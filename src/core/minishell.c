/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/09/06 08:45:50 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		g_sig = 0;

void	main_loop(t_shell *sh)
{
	t_cmd	*root;

	if (sh->line)
	{
		root = do_lexing(sh);
		// ft_printf("<<<-----LEXING----->>>\n");
		// ft_printf("\n");
		// print_tree(&root);
		do_parsing(root);
		// expander(sh, sh->root);
		// ft_printf("<<<-----PARSING----->>>\n");
		// ft_printf("\n");
		// print_tree(&root);
		execute(root);
		free_tree(root);
	}
	while (true)
	{
		sh->line = readline(MINISHELL_PROMPT);
		if (ft_strlen(sh->line) == 0)
			continue;
		root = do_lexing(sh);
		// ft_printf("<<<-----LEXING----->>>\n");
		// ft_printf("\n");
		// print_tree(&root);
		do_parsing(root);
		// expander(sh, sh->root);
		// ft_printf("<<<-----PARSING----->>>\n");
		// ft_printf("\n");
		// print_tree(&root);
		sh->ret = execute(root);
		free_tree(root);
		free(sh->line);
		printf("%s", NO_COLOR);
	}
}

/// @brief main function of minishell
/// @param argc input arg count
/// @param argv arg values
/// @param env env values
/// @return exit code
int	main(int argc, char **argv, char **env)
{
	t_shell	sh;

	init(&sh, argc, argv, env);
	// signals()
	main_loop(&sh);
}
