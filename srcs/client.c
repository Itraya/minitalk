/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrang <mlagrang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:43:41 by mlagrang          #+#    #+#             */
/*   Updated: 2022/01/19 18:20:10 by mlagrang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	useless(int sig)
{
	(void)sig;
}

void	ft_error(int sig)
{
	(void)sig;
	exit(EXIT_FAILURE);
}

void	send_byte(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		pause();
		if (c & 1 << bit)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		bit++;
	}
}

void	send_msg(int pid, char *msg)
{
	int	i;

	i = 0;
	kill(pid, SIGUSR1);
	//sleep(100);
	while (msg[i])
	{
		send_byte(pid, msg[i]);
		i++;
	}
	send_byte(pid, '\0');
}

int	main(int ac, char **av)
{
	if (ac != 3)
		return (0);
	signal(SIGUSR2, useless);
	signal(SIGUSR1, ft_error);
	send_msg(atoi(av[1]), av[2]);
}
