/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/09/17 01:35:54 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_sig = 0;

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
			f_exit2("exit", EXIT_SUCCESS);
		if (ft_strlen(sh->line) == 0)
			continue;
		add_history(sh->line);
		if (!quote_check(sh->line))
		{
			free(sh->line);
			continue;
		}
		root = do_lexing(sh);
		ft_printf("<<<-----PARSING----->>>\n");
		ft_printf("\n");
		print_tree(&root);
		// do_parsing(root);
		expander(sh, root);
		ft_printf("<<<-----EXPANDING----->>>\n");
		ft_printf("\n");
		print_tree(&root);
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

	signal(SIGINT, &signal_handler);
	init(&sh, argc, argv, env);
	main_loop(&sh);
}
