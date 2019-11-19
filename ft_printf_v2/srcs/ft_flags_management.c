/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereligi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:11:46 by jereligi          #+#    #+#             */
/*   Updated: 2019/11/19 15:46:10 by jereligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		ft_flag_width(t_data *data)
{
	int	precision;
	
	if (data->precision > 0)
		precision = data->precision;
	else
		precision = ft_get_strlen(data);
	while (precision++ < data->width)
		ft_putchar(' ', data);
	ft_display_management(data);	
}

static void		ft_flag_zero(t_data *data)
{
	if (ft_nb_is_negative(data))
		ft_exception_flag_zero(data);
	else
	{
		int	precision;
		
		if (data->precision > 0)
			precision = data->precision;
		else
			precision = ft_get_strlen(data);
		while (precision++ < data->width)
			ft_putchar('0', data);
		ft_display_management(data);
	}
}

static void		ft_flag_minus(t_data *data)
{
	int	precision;

	ft_display_management(data);
	if (data->precision > 0)
		precision = data->precision;
	else
		precision = ft_get_strlen(data);
	while (precision++ < data->width)
		ft_putchar(' ', data);
}

void			ft_flags_management(t_data *data)
{
	if (data->flags == '-')
		ft_flag_minus(data);
	else if (data->flags == '0')
		ft_flag_zero(data);
	else if (data->width > 0)
		ft_flag_width(data);
	else
		ft_display_management(data);
}