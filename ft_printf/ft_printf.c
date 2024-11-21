/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakoako <trakoako@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:15:41 by trakoako          #+#    #+#             */
/*   Updated: 2024/11/21 18:21:43 by trakoako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include <unistd.h>
#include "stdio.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (ft_putstr("(null)"));
	while (str[i] != '\0')
		i++;
	return (write(1, str, i));
}

int	ft_putnbr(int nb)
{
	char	c;

	if (nb == -2147483648)
		return (ft_putstr("-2147483648"));
	if (nb < 0)
		return (write(1, "-", 1) + ft_putnbr(-nb));
	c = nb % 10 + '0';
	if (nb > 9)
		return(ft_putnbr(nb / 10) + write(1, &c, 1));
	return(write(1, &c, 1));
}

int	ft_puthex(unsigned int nb)
{
	char	str[16] = "0123456789abcdef";

    if (nb > 16)
        return(ft_puthex(nb / 16) + write(1, &str[nb % 16], 1));
    return(write(1, &str[nb % 16], 1));
}

int ft_printf(const char *str, ...)
{
	va_list	arg;
	int	i;
	int	count;

	i = 0;
	count = 0;
	va_start(arg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 's')
				count += ft_putstr(va_arg(arg, char *));
			else if (str[i] == 'd')
				count += ft_putnbr(va_arg(arg, int));
			else if (str[i] == 'x')
				count += ft_puthex(va_arg(arg, unsigned int));
		}
		else
                count += write(1, &str[i], 1);
		i++;
	}
	va_end(arg);
	return (count);
}
