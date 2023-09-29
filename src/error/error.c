/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:15:15 by flauer            #+#    #+#             */
/*   Updated: 2023/09/29 10:44:12 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error(char *msg, char *errmsg, int excode)
{
	if (msg)
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", msg, errmsg);
	else
		ft_fprintf(STDERR_FILENO, "minishell: %s\n", errmsg);
	exit(excode);
}

void	ft_error2(char *msg, char *errmsg, void *tofree)
{
	if (msg)
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", msg, errmsg);
	else
		ft_fprintf(STDERR_FILENO, "minishell: %s\n", errmsg);
	if (tofree)
		free(tofree);
}

void	ft_error3(char *msg, char *errmsg, int excode, void *tofree)
{
	if (msg)
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", msg, errmsg);
	else
		ft_fprintf(STDERR_FILENO, "minishell: %s\n", errmsg);
	free(tofree);
	exit(excode);
}

void	ft_error4(t_shell *sh, char *msg, char *errmsg, void *tofree)
{
	if (msg)
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n", msg, errmsg);
	else
		ft_fprintf(STDERR_FILENO, "minishell: %s\n", errmsg);
	if (tofree)
		free(tofree);
	sh->ret = GENERAL_ERROR;
}
