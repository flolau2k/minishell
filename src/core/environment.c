/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:11:16 by flauer            #+#    #+#             */
/*   Updated: 2023/08/24 14:48:36 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	len = array_len(*env);
	if (newval)
		len = array_len(*env) + 1;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		ft_error("malloc error!", GENERAL_ERROR);
	while (i < (len - 1))
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	if (newval)
	{
		ret[i] = newval;
		free_arr(&env);
	}
	return (ret);
}

/// @brief get a single value of a given key from the environment
/// @param env the environment
/// @param key desired key
/// @return string with the value or NULL, if key is not in the environment.
/// return may be free'd if not NULL.
char	*get_env(char *env[], char *key)
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

char	*get_cmd_path(char *name, char *env[])
{
	char	**paths;
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	paths = get_env(env, "PATH");
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(path, name);
		free(path);
		if (!access(cmd, X_OK))
			break ;
		free(cmd);
		cmd = NULL;
		++i;
	}
	free_splits(paths);
	return (cmd);
}

char	*get_cmd(char *name, char *env[])
{
	if (!name)
		return (NULL);
	else if (ft_strnstr(name, "/", ft_strlen(name)))
		return (ft_strdup(name));
	else
		return (get_cmd_path(name, env));
}
