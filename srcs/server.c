/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:21:06 by mlagrang          #+#    #+#             */
/*   Updated: 2022/01/19 18:25:43 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

unsigned char	*g_s = NULL;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	long int	nb;

	nb = n;
	if (n < 0)
	{
		nb = nb * -1;
		ft_putchar('-');
	}
	if (nb >= 10)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
}

unsigned char	*ft_join(unsigned char *a, char b)
{
	int				i;
	unsigned char	*s;

	if (!a || !a[0])
		a = NULL;
	i = 0;
	while (a && a[i])
		i++;
	s = malloc(i + 2);
	if (s)
	{
		i = -1;
		while (a && a[++i])
			s[i] = a[i];
		if (i == -1)
			i = 0;
		s[i] = b;
		s[i + 1] = '\0';
	}
	free(a);
	return (s);
}

void	get_msg(int sig, siginfo_t *a, void *b)
{
	static int					bit = -1;
	static unsigned char		c = 0;
	static int					pid = -1;

	(void)b;
	if (pid == -1)
		pid = a->si_pid;
	if (sig == SIGUSR2)
		c |= 1 << bit;
	bit++;
	if (bit == 8)
	{
		bit = 0;
		g_s = ft_join(g_s, c);
		if (c == '\0')
		{
			dprintf(1, "%s", g_s);
			free(g_s);
			g_s = NULL;
			bit = -1;
		}
		c = 0;
	}
	if (a->si_pid == 0)
	{
		kill(pid, SIGUSR1);
		pid = -1;
		c = 0;
		bit = -1;
		free(g_s);
		g_s = NULL;
		dprintf(1, "\na\n");
	}
	else
		kill(a->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	a;

	a.sa_sigaction = get_msg;
	a.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	ft_putnbr(getpid());
	write(1, "\n", 1);
	sigaction(SIGUSR1, &a, 0);
	sigaction(SIGUSR2, &a, 0);
	while (1)
		pause();
}
