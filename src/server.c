/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameneze <mameneze@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 21:52:14 by mameneze          #+#    #+#             */
/*   Updated: 2021/09/27 22:27:03 by mameneze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	handler(int sig, siginfo_t *sa, void *context)
{
	static unsigned int		count;
	static unsigned char	c;
	char					mask;

	(void)context;
	if (count > 7)
	{
		count = 0;
		c = 0;
	}
	mask = 1 << count;
	if (sig == SIGUSR1)
		c = c | mask;
	if (sig == SIGUSR2)
		c = c & ~mask;
	count++;
	if (count == 8)
	{
		if (c == 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			kill(sa->si_pid, SIGUSR1);
		}
		ft_putchar(c);
	}
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	sa.sa_sigaction = &handler;
	sa.sa_flags = SA_SIGINFO;
	pid = getpid();
	write(1, "PID: ", 5);
	ft_putnbr(pid);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
