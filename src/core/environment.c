/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:11:16 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 16:17:11 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief add new value to internal env array. If newval is NULL, env will be
/// copied and returned. The single values will be deep-copied. Old env
/// pointer will be free'd if newval is not NULL.
/// @param env old env pointer
/// @param newval new string to put in
/// @return new env pointer.
char	**set_env(char **env, char *newval)
{
	int		len;
	int		i;
	char	**ret;

	i = 0;
	len = array_len(env);
	if (newval)
		len++;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		ft_error("malloc error!", GENERAL_ERROR);
	ret[len] = NULL;
	while (i < len)
	{
		if (newval && i == len - 1)
			ret[i] = ft_strdup(newval);
		else
			ret[i] = ft_strdup(env[i]);
		i++;
	}
	if (newval)
		free_arr(env);
	return (ret);
}

/// @brief get a single value of a given key from the environment
/// @param env the environment
/// @param key desired key
/// @return string with the value or NULL, if key is not in the environment.
/// return may be free'd if not NULL.
char	*get_env(char **env, char *key)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (ft_strlen(key) == 0)
		return (NULL);
	while (env[i])
	{
		if (ft_strnstr(env[i], key, ft_strlen(key)))
		{
			ret = ft_substr(env[i], ft_strlen(key) + 1, \
				ft_strlen(env[i]) - ft_strlen(key) - 1);
			return (ret);
		}
		++i;
	}
	return (NULL);
}

char	**unset_env(char **env, char *val)
{
	int	i;
	int	len;

	i = 0;
	len = array_len(env);
	if (!val || len == 0 || ft_strlen(val) == 0)
		return (env);
	while (i < len && ft_strncmp(val, env[i], ft_strlen(val)))
		i++;
	while (i < (len - 1))
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
	return (env);
}	