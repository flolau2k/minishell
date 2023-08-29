/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:15:15 by flauer            #+#    #+#             */
/*   Updated: 2023/08/29 15:47:26 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
