/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcazac <pcazac@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:46:19 by pcazac            #+#    #+#             */
/*   Updated: 2023/09/22 13:43:10 by pcazac           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**create_arr(char *new)
{
	char **ret;

	ret = ft_calloc(2, sizeof(char *));
	if (!ret)
		ft_error("malloc", strerror(errno), GENERAL_ERROR);
	ret[0] = ft_strdup(new);
	return (ret);
}

char	**array_addback(char **argv, char *new)
{
	int		len;
	int		i;
	char	**ret;

	i = 0;
	if (!new)
		return (argv);
	if (!argv)
		return (create_arr(new));
	len = array_len(argv) + 1;
	ret = ft_calloc((len + 1), sizeof(char *));
	if (!ret)
		ft_error("malloc", strerror(errno), GENERAL_ERROR);
	while (i < len)
	{
		if (i == len - 1)
			ret[i] = ft_strdup(new);
		else
			ret[i] = ft_strdup(argv[i]);
		i++;
	}
	if (argv)
		free_arr(argv);
	return (ret);
}
