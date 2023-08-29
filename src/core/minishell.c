/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:04:24 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 11:47:25 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	main_loop(t_shell *sh)
{
	char	*line;
	t_cmd	*root;

	while (true)
	{
		line = readline(MINISHELL_PROMPT);
		root = parse(line);
		free(line);
		execute(root);
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
