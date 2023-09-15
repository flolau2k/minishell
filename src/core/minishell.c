/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/09/15 11:21:34 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_sig = 0;

void	reset_shell(t_shell *sh)
{
	dup2(sh->ttyin, STDIN_FILENO);
	dup2(sh->ttyout, STDOUT_FILENO);
	printf("%s", NO_COLOR);
}

void	main_loop(t_shell *sh)
{
	t_cmd	*root;

	while (true)
	{
		if (!g_sig)
			sh->line = readline(MINISHELL_PROMPT);
		else
			sh->line = readline("");
		g_sig = 0;
		if (!sh->line)
			f_exit2(sh, "exit", EXIT_SUCCESS);
		if (ft_strlen(sh->line) == 0)
			continue ;
		add_history(sh->line);
		root = do_lexing(sh);
		do_parsing(root);
		if (!quote_check(root))
		{
			free_init_tree(root);
			free(sh->line);
			continue ;
		}
		expander(sh, root);
		// ft_printf("<<<-----PARSING----->>>\n");
		// ft_printf("\n");
		// print_tree(&root);
		free(sh->line);
		sh->line = NULL;
		rec_execute(root);
		reset_shell(sh);
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

	signal(SIGINT, &signal_handler);
	init(&sh, argc, argv, env);
	main_loop(&sh);
}
