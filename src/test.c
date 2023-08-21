/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:57:56 by flauer            #+#    #+#             */
/*   Updated: 2023/08/21 18:29:12 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)env;
	(void)argc;
	(void)argv;
	int	i = 0;
	char **tokens = do_lexing("<here cat | fdks asdf asdfadsfjljadsf\"adsfadsf\" 'adsfadgsa\"asdf\"' | grep >out");
	while (tokens[i])
	{
		ft_printf("%s\n", tokens[i]);
		i++;
	}
	return (0);
}