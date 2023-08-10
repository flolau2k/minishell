/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:15:15 by flauer            #+#    #+#             */
/*   Updated: 2023/08/10 10:21:51 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

ft_error(t_shell *shell)
{
	// free all malloced pointers and exit with appropriate Exitcode 
	// (see header)
	exit(GENERAL_ERROR);
}
