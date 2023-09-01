/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:23:26 by flauer            #+#    #+#             */
/*   Updated: 2023/09/01 12:41:49 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/// @brief free a string array and it's contents.
/// @param arr array
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

/// @brief get lenth of string array
/// @param arr array
/// @return length
int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return i;
}

/// @brief get the values of a given key from the environment
/// @param env the environment
/// @param key desired key
/// @return string array with the values, NULL if the key is not in environment.
/// return may be free'd if not NULL.
char	**get_env_arr(char *env[], char *key)
{
	char	**ret;
	char	*val;

	val = get_env(env, key);
	if (!val)
		return (NULL);
	ret = ft_split(val, ':');
	free(val);
	return (ret);
}

void	print_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
