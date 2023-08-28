/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testasdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:02:08 by flauer            #+#    #+#             */
/*   Updated: 2023/08/28 17:18:06 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "stdio.h"
#include <fcntl.h>
// #include <readline/readline.h>
#include "libft/include/libft.h"

int	exec(char **env)
{
	pid_t	pid;
	int		stat_loc;

	pid = fork();
	if (pid == 0)
	{
		char	*argv[2] = {"head", "-1"};
		execve("head", argv, env);
	}
	waitpid(pid, &stat_loc, 0);
	return (WEXITSTATUS(stat_loc));
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int	fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		// dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		char	*argv[2] = {"/bin/cat", "/dev/urandom"};
		execve("/bin/cat", argv, env);
	}
	else
	{
		// dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		exec(env);
	}
	// printf("done\n");
	return (0);
}

// int	main(void)
// {
// 	int	fd1;
// 	int	fd2;
// 	char	*line;

// 	fd1 = open("asf.txt", O_RDONLY);
// 	fd2 = open("asf.txt", O_WRONLY);

// 	line = get_next_line(fd1);
// 	while (line)
// 	{
// 		printf("%s\n", line);
// 		line = get_next_line(fd1);
// 	}
// 	write(fd2, "Hello Petru Hello Petru\n", 12);
// 	line = get_next_line(fd1);
// 	while (line)
// 	{
// 		printf("%s\n", line);
// 		line = get_next_line(fd1);
// 	}

// 	printf("exiting!\n");
// 	return (0);
// }
