/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:15:15 by flauer            #+#    #+#             */
/*   Updated: 2023/09/14 15:40:50 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error(char *msg, int excode)
{
	char	*message;

	if (msg)
	{
		message = ft_strjoin("minishell: ", msg);
		perror(message);
		free(message);
	}
	else
		perror("minishell: ");
	exit(excode);
}

void	ft_error2(char *msg, int excode)
{
	if (msg)
		printf("minishell: %s\n", msg);
	exit(excode);
}
