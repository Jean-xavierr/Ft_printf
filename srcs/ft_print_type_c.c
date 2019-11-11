/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type_c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereligi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 11:14:35 by jereligi          #+#    #+#             */
/*   Updated: 2019/11/11 13:27:53 by jereligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_print_type_c(va_list ap, t_storage *storage)
{
	int	i;

	i = 0;
	if (storage->flags == '0')
	{
		while (i++ < storage->flags_nb - 1)
			write(1, "0", 1);
		ft_putchar((char)va_arg(ap, int));
	}
	else if (storage->flags == '-')
	{
		ft_putchar((char)va_arg(ap, int));
		while (i++ < storage->flags_nb - 1)
			write(1, " ", 1);
	}
	else if (storage->width >= 1)
	{
		while (i++ < storage->width - 1)
			write(1, " ", 1);
		ft_putchar((char)va_arg(ap, int));
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}