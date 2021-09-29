/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameneze <mameneze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 18:11:03 by mameneze          #+#    #+#             */
/*   Updated: 2021/09/28 21:13:34 by mameneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	pass_char(int pid, unsigned char c)
{
	int	i;
	int	result;

	i = 0;
	while (i <= 7)
	{
		if (c & (1 << i))
			result = kill(pid, SIGUSR1);
		else
			result = kill(pid, SIGUSR2);
		if (result == -1)
		{
			write(STDERR_FILENO, "Wrong PID\n", 11);
			exit (1);
		}
		usleep(500);
		i++;
	}
}

static int	get_pnumber(char *argv)
{
	int	id;

	id = 0;
	while (*argv)
	{
		if (*argv >= '0' && *argv <= '9')
			id = (id * 10) + (*argv - '0');
		else
			return (0);
		 argv++;
	}
	return (id);
}

static void	msg_confirmation(int sig)
{
	if (sig == SIGUSR1)
		write(STDOUT_FILENO, "Message received by Server!\n", 29);
	if (sig == SIGUSR2)
	{
	}
	usleep(500);
}

int	main(int argc, char *argv[])
{
	pid_t	pid;

	if (argc != 3)
		return (write(STDERR_FILENO, ERRARGC, 59), 0);
	signal(SIGUSR1, msg_confirmation);
	signal(SIGUSR2, msg_confirmation);
	pid = get_pnumber(argv[1]);
	if (!pid)
		return (write(STDERR_FILENO, ERRARGC, 59), 0);
	while (*argv[2])
	{
		pass_char(pid, *argv[2]);
		argv[2]++;
	}
	pass_char(pid, '\0');
}
