/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:test.c
/*   Created: 2023/08/22 12:02:08 by flauer            #+#    #+#             */
/*   Updated: 2023/08/24 12:15:45 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"
#include "libft/include/libft.h"

void	free_arr(char ***arr)
{
	int		i;
	char	**a;

	a = *arr;
	i = 0;
	while (a && a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
	*arr = NULL;
}

int	main(void)
{
	char	**fcns;
	int		i;

	//fcns = (char *[]){"1", "2", "3", "4", "5", "6", "7", NULL};
	fcns = malloc(sizeof(char *) * 8);
	i = 0;
	while (i < 7)
	{
		fcns[i] = ft_strdup("1");
		i++;
	}
	fcns[i] = NULL;
	free_arr(&fcns);
	return (0);
=======
/*   Created: 2023/08/10 10:26:59 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 14:33:07 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	init(t_shell *sh, int argc, char **argv, char **env)
{
	if (argc > 2)
		ft_error("put your args as one string please!", GENERAL_ERROR);
	*sh = (t_shell){};
	if (argc == 2)
		sh->line = argv[1];
	sh->env = set_env(env, NULL);
	return (true);
>>>>>>> 895cb005ee6a47f2222441d90024a4ffc9437df1:src/parse/init.c
}
