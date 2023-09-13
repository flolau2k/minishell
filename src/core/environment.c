/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:11:16 by flauer            #+#    #+#             */
/*   Updated: 2023/09/13 16:20:59 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**copy_env(char **env)
{
	int		len;
	int		i;
	char	**ret;

	i = 0;
	len = array_len(env);
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		ft_error("malloc error!", GENERAL_ERROR);
	ret[len] = NULL;
	while (i < len)
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	ret = set_default_env(ret);
	return (ret);
}

/// @brief add new value to internal env array. Old env pointer will be free'd.
/// if newval is NULL, env is returned.
/// @param env old env pointer
/// @param newval new string to put in
/// @return new env pointer.
char	**set_env(char **env, char *newval)
{
	int		len;
	int		i;
	char	**ret;

	i = 0;
	if (!newval)
		return (env);
	len = array_len(env) + 1;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		ft_error("malloc error!", GENERAL_ERROR);
	ret[len] = NULL;
	while (i < len)
	{
		if (i == len - 1)
			ret[i] = ft_strdup(newval);
		else
			ret[i] = ft_strdup(env[i]);
		i++;
	}
	free_arr(env);
	return (ret);
}

bool	replace_in_env(char **env, char *new)
{
	int		len;
	int		i;
	char	*name;

	name = ft_substr(new, 0, ft_strchr(new, '=') - new + 1);
	i = 0;
	len = array_len(env);
	while (i < len)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
		{
			ft_bzero(env[i], ft_strlen(env[i]));
			free(env[i]);
			free(name);
			env[i] = ft_strdup(new);
			return (true);
		}
		i++;
	}
	return (false);
}

/// @brief get a single value of a given key from the environment
/// @param env the environment
/// @param key desired key
/// @return string with the value or NULL, if key is not in the environment.
/// returned value points directly to the env, do not modify or free!
char	*get_env(char **env, char *key)
{
	int		i;
	char	*ret;
	char	*ekey;

	i = 0;
	ret = NULL;
	if (ft_strlen(key) == 0)
		return (NULL);
	ekey = ft_strjoin(key, "=");
	while (env[i])
	{
		if (ft_strnstr(env[i], ekey, ft_strlen(ekey)))
		{
			ret = env[i] + ft_strlen(ekey);
			free(ekey);
			return (ret);
		}
		++i;
	}
	free(ekey);
	return (NULL);
}

char	**unset_env(char **env, char *val)
{
	int		i;
	int		len;
	char	*key;

	i = 0;
	len = array_len(env);
	if (!val || len == 0 || ft_strlen(val) == 0)
		return (env);
	key = ft_strjoin(val, "=");
	while (i < len && ft_strncmp(key, env[i], ft_strlen(key)))
		i++;
	free(env[i]);
	while (i < (len - 1))
	{
		env[i] = env[i + 1];
		i++;
	}
	env[i] = NULL;
	free(key);
	return (env);
}
