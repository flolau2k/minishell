/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:20:22 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/22 18:20:27 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Returns malloced the special variable
/// @param sh Shell struct pointer
/// @param ret Return expanded string
/// @return Returns expanded variable
int	get_special_var(t_shell *sh, char **ret)
{
	char	*tmp;
	char	*val;

	val = ft_itoa(sh->ret);
	tmp = *ret;
	if (!tmp)
	{
		*ret = val;
		return (1);
	}
	*ret = ft_strjoin(tmp, val);
	free(tmp);
	return (1);
}

/// @brief Returns malloced expanded variable
/// @param sh Shell struct pointer
/// @param arg Argument passed to be expanded
/// @param ret Return expanded string
/// @return Returns a malloced string with the expanded variable
int	get_variable(t_shell *sh, char *arg, char **ret)
{
	char	*tmp;
	char	*val;
	int		i;

	i = 0;
	i += is_variable(sh, arg + 1, &val);
	tmp = *ret;
	if (!tmp)
	{
		*ret = val;
		return (i);
	}
	*ret = ft_strjoin(tmp, val);
	free(tmp);
	return (i);
}

/// @brief Returns malloced non variable
/// @param arg Argument passed to be copied
/// @param ret Return non-expanded string
/// @return Returns a malloced string with the non-expanded variable
int	get_non_variable(char *arg, char **ret)
{
	char	*tmp;
	char	*val;
	int		i;

	i = 0;
	i += not_variable(arg, &val);
	tmp = *ret;
	if (!tmp)
	{
		*ret = val;
		return (i);
	}
	*ret = ft_strjoin(tmp, val);
	free(tmp);
	return (i);
}