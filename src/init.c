/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:26:59 by flauer            #+#    #+#             */
/*   Updated: 2023/08/10 10:46:34 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_tokens(char ***tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

bool	init(t_shell *shell, int argc, char **argv, char **env)
{
	int	i;

	i = 1;
	*shell = (t_shell){};
	shell->tokens = ft_calloc(argc, sizeof(char *));
	if (!shell->tokens)
		return (false);
	while (i < argc)
	{
		shell->tokens[i - 1] = ft_strdup(argv[i]);
		if (!shell->tokens[i - 1])
		{
			free_tokens(shell->tokens);
			shell->tokens = NULL;
		}
		i++;
	}
	return (true);
}
