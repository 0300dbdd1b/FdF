/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaddino <noaddino@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:37:48 by noaddino          #+#    #+#             */
/*   Updated: 2025/04/14 17:42:01 by noaddino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../libft.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	size_t	i;

	if (!str)
		return (write(1, "(null)", 6));
	i = 0;
	while (str[i])
		i++;
	write(1, str, i);
	return (i);
}

int	ft_puthex(long long int nbr, int uppercase)
{
	if (uppercase)
		return (ft_putnbr_base_unsigned(nbr, BASE16UP));
	return (ft_putnbr_base_unsigned(nbr, BASE16LOW));
}

int	ft_putptr(void *ptr)
{
	unsigned long	addr;
	char			buf[32];
	char			*base;
	int				i;
	int				count;

	addr = (unsigned long)ptr;
	base = "0123456789abcdef";
	i = 0;
	if (addr == 0)
		return (write(1, "0x0", 3));
	while (addr > 0)
	{
		buf[i] = base[addr % 16];
		addr = addr / 16;
		i = i + 1;
	}
	count = write(1, "0x", 2);
	while (i > 0)
	{
		i = i - 1;
		write(1, &buf[i], 1);
		count = count + 1;
	}
	return (count);
}
