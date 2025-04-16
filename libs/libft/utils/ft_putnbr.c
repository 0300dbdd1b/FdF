/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaddino <noaddino@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:24:16 by noaddino          #+#    #+#             */
/*   Updated: 2025/04/14 17:45:01 by noaddino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putnbr(int n)
{
	long	nb;
	int		count;
	char	c;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		count = count + write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		count = count + ft_putnbr(nb / 10);
	c = (nb % 10) + '0';
	count = count + write(1, &c, 1);
	return (count);
}

static unsigned long	ft_base_len(const char *base)
{
	unsigned long	len;

	len = 0;
	while (base[len])
		len = len + 1;
	return (len);
}

static int	ft_print_buf_reverse(char *buf, int size)
{
	int	count;

	count = 0;
	while (size > 0)
	{
		size = size - 1;
		write(1, &buf[size], 1);
		count = count + 1;
	}
	return (count);
}

int	ft_putnbr_base_unsigned(unsigned long nbr, const char *base)
{
	unsigned long	base_len;
	char			buf[32];
	int				i;

	base_len = ft_base_len(base);
	if (base_len < 2)
		return (0);
	if (nbr == 0)
		return (write(1, &base[0], 1));
	i = 0;
	while (nbr > 0)
	{
		buf[i] = base[nbr % base_len];
		nbr = nbr / base_len;
		i = i + 1;
	}
	return (ft_print_buf_reverse(buf, i));
}

int	ft_putnbr_unsigned(unsigned int n)
{
	char	c;
	int		count;

	count = 0;
	if (n >= 10)
		count = count + ft_putnbr_unsigned(n / 10);
	c = (n % 10) + '0';
	count = count + write(1, &c, 1);
	return (count);
}
