/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:57:56 by flauer            #+#    #+#             */
/*   Updated: 2023/08/21 13:50:23 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)env;
	(void)argc;
	(void)argv;
	int	i = 0;
	char **tokens = do_lexing("asdf asdfadsfjljadsf\"adsfadsf\" 'adsfadgsa\"asdf\"'");
	while (tokens[i])
	{
		ft_printf("%s\n", tokens[i]);
		i++;
	}
	return (0);
}