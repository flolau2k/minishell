/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/09/22 10:36:03 by flauer           ###   ########.fr       */
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
		if (isatty(fileno(stdin)))
			sh->line = readline(MINISHELL_PROMPT);
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			sh->line = line;
			if (line)
				sh->line = ft_strtrim(line, "\n");
			free(line);
		}
		// sh->line = readline(MINISHELL_PROMPT);
		apply_signal(sh);
		if (!sh->line)
			f_exit2(sh, NULL, EXIT_SUCCESS);
		if (ft_strlen(sh->line) == 0)
			continue ;
		add_history(sh->line);
		if (!quote_check(sh->line))
		{
			free(sh->line);
			continue ;
		}
		root = do_lexing(sh);
		expander(sh, root);
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
