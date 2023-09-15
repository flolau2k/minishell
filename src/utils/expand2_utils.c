/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:20:22 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/15 16:40:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief Returns malloced the special variable
/// @param sh Shell struct pointer
/// @param ret Return expanded string
/// @return Returns expanded variable
int	get_special_var(t_shell *sh, char **ret)
{
	int		count;
	int		i;
	char	*new;
	char	*s;

	count = 0;
	i = 0;
	s = NULL;
	new = NULL;
	i = is_special_variable(sh, &s);
	if (s)
		count += ft_strlen(s);
	if (!*ret)
		*ret = s;
	else
	{
		new = ft_strdup(*ret);
		free(*ret);
		*ret = ft_realloc(new, s, count);
	}
	return (i);
}

/// @brief Returns malloced expanded variable
/// @param sh Shell struct pointer
/// @param arg Argument passed to be expanded
/// @param ret Return expanded string
/// @return Returns a malloced string with the expanded variable
int	get_variable(t_shell *sh, char *arg, char **ret)
{
	int		count;
	int		i;
	char	*new;
	char	*s;
	
	count = 0;
	i = 0;
	s = NULL;
	new = NULL;
	i += is_variable(sh, arg + i, &s);
	if (s)
		count += ft_strlen(s);
	if (!*ret)
		*ret = s;
	else
	{
		new = ft_strdup(*ret);
		free(*ret);
		*ret = ft_realloc(new, s, count);
	}
	return (i);
}

/// @brief Returns malloced non variable
/// @param arg Argument passed to be copied
/// @param ret Return non-expanded string
/// @return Returns a malloced string with the non-expanded variable
int	get_non_variable(char *arg, char **ret)
{
	int		count;
	int		i;
	char	*new;
	char	*s;
	
	count = 0;
	i = 0;
	s = NULL;
	new = NULL;
	i += not_variable(arg + i, &s);
	if (s)
		count += ft_strlen(s);
	if (!*ret)
		*ret = s;
	else
	{
		new = ft_strdup(*ret);
		free(*ret);
		*ret = ft_realloc(new, s, count);
	}
	return (i);
}
