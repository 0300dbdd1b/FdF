/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noaddino <noaddino@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:37:56 by noaddino          #+#    #+#             */
/*   Updated: 2025/04/14 17:37:57 by noaddino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_format(const char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (format == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	else if (format == 'x')
		return (ft_puthex(va_arg(args, unsigned int), 0));
	else if (format == 'X')
		return (ft_puthex(va_arg(args, unsigned int), 1));
	else if (format == 'p')
		return (ft_putptr(va_arg(args, void *)));
	else if (format == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		printed;

	va_start(args, str);
	i = 0;
	printed = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			printed += ft_format(str[i + 1], args);
			i++;
		}
		else
			printed += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (printed);
}
