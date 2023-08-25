/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:02:08 by flauer            #+#    #+#             */
/*   Updated: 2023/08/25 14:25:55 by flauer           ###   ########.fr       */
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

const static char	*g_fcn_n[] = 
{
	"echo",
	"cd",
	"env",
	"exit",
	"export",
	"pwd",
	"unset"
};

int	main(void)
{
	char	**fcns;
	int		i;

	fcns = (char *[]){"1", "2", "3", "4", "5", "6", "7", NULL};
	i = 0;
	while (i < 8)
	{
		printf("%s\n", g_fcn_n[i]);
		i++;
	}
	// fcns = malloc(sizeof(char *) * 8);
	// i = 0;
	// while (i < 7)
	// {
	// 	fcns[i] = ft_strdup("1");
	// 	i++;
	// }
	// fcns[i] = NULL;
	// int	pid = fork();
	// if (pid == 0)
	// {
	// 	fcns[2] = ft_strdup("5");
	// 	printf("child exited!\n");
	// }
	// else
	// {
	// 	usleep(100);
	// 	printf("%s\n", fcns[2]);
	// 	if (fcns[2][0] == '5')
	// 		printf("true\n");
	// 	else
	// 		printf("false\n");
	// }
	// free_arr(&fcns);
	return (0);
}
