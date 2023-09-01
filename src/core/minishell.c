/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 16:52:14 by flauer           ###   ########.fr       */
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
		do_parsing(root);
		execute(root);
	}
	while (true)
	{
		sh->line = readline(MINISHELL_PROMPT);
		if (ft_strlen(sh->line) == 0)
			continue;
		root = do_lexing(sh);
		do_parsing(root);
		sh->ret = execute(root);
		free(sh->line);
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
