/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:57:56 by flauer            #+#    #+#             */
/*   Updated: 2023/08/24 14:08:30 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)env;
	(void)argc;
	(void)argv;
	int	i = 0;
	char **tokens = do_lexing("< <here cat | fdks asdf asdfadsfjljadsf\"adsfadsf\" 'adsfadgsa\"asdf\"' asd|ads grep > >out");
	while (tokens[i])
	{
		ft_printf("%s\n", tokens[i]);
		i++;
	}
	return (0);
}
void	f_echo(t_exec *cmd)
{
	int		i;
	bool	nl;

	nl = true;
	i = 1;
	if (cmd->argv[1] && ft_strncmp(cmd->argv[1], "-n", 3) == 0)
	{
		nl = false;
		i = 2;
	}
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		i++;
	}
	if (nl)
		printf("\n");
	return (free_exec(cmd));
}
