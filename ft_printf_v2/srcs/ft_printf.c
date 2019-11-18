/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereligi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:44:05 by jereligi          #+#    #+#             */
/*   Updated: 2019/11/18 15:30:01 by jereligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		ft_check_is_width(int i, t_data *data)
{
	if (data->set[i] >= '0' && data->set[i] <= '9')
	{
		data->width = 0;
		while (data->set[i] >= '0' && data->set[i] <= '9')
			data->width = data->width * 10 + (data->set[i++] - '0');
	}
	else if (data->set[i] == '*')
	{
		data->width = 0;
		if (ft_is_convers(data->set[i + 1]) || data->set[i + 1] == '*')
		{
			data->width = va_arg(data->ap, int);
			if (data->width < 0)
			{
				data->flags = '-';
				data->width = data->width * -1;
			}
			i++;
		}
		else
			while (data->set[i] >= '0' && data->set[i] <= '9')
				data->width = data->width * 10 + (data->set[i++] - '0');
	}
	return (i);
}

static int		ft_check_is_minus_or_zero(int i, t_data *data)
{
	if (data->set[i] == '-')
	{
		data->width = 0;
		data->flags = '-';
		i++;
		if (data->set[i] >= '0' && data->set[i] <= '9')
			while (data->set[i] >= '0' && data->set[i] <= '9')
				data->width = data->width * 10 + (data->set[i++] - '0');
		else if (data->set[i++] == '*')
			data->width = va_arg(data->ap, int);
	}
	else if (data->set[i] == '0' && data->flags != '-')
	{
		data->width = 0;
		data->flags = '0';
		i++;
		if (data->set[i] >= '0' && data->set[i] <= '9')
			while (data->set[i] >= '0' && data->set[i] <= '9')
				data->width = data->width * 10 + (data->set[i++] - '0');
		else if (data->set[i++] == '*')
			data->width = va_arg(data->ap, int);
	}
	return (i);
}

void			ft_check_flags(t_data *data)
{
	int i;
	int	n;

	i = 0;
	n = 0;
	while (data->set[i])
	{
		if (i < (n = ft_check_is_minus_or_zero(i, data)))
			i = n;
		else if (i < (n = ft_check_is_width(i, data)))
			i = n;
		else if (data->set[i++] == '.')
		{
			if (data->set[i] != '*')
				while (data->set[i] >= '0' && data->set[i] <= '9')
					data->precision = data->precision *
						10 + (data->set[i++] - '0');
			else if (data->set[i++] == '*')
				data->precision = va_arg(data->ap, int);
		}
		else if (i < (n = ft_check_is_width(i, data)))
			i = n;
		else
			i++;
	}
}

int				ft_check_string(int i, t_data *data)
{
	int	n;
	
	n = 0;
	ft_reinit_flags(data);
	while ((ft_check_set(data->str[i]) && data->str[i]))
	{
		data->set = ft_strjoin_char(data->set, data->str[i]);
		if (ft_is_convers(data->str[i]))
		{
			data->convers = data->str[i++];
			break ;
		}
		i++;
	}
	printf("set = %s\n", data->set);
	ft_check_flags(data);
	printf("flags = %c\n", data->flags);
	printf("flags_width = %d\n", data->width);
	printf("flags_pre = %d\n", data->precision);
	printf("data->c = %c\n\n", data->convers);
	data->arg = va_arg(data->ap, int);
	while (data->set[n++])
	{
		if (ft_is_char(data->set[n]))
		{
			data->convers = data->set[n];
			ft_flags_management(data);
			break ;
		}	
		else if (data->set[n + 1] == '\0')
		{
			ft_flags_management(data);
			n++; ;
		}
	}
	return (i);
}

int				ft_printf(const char *s, ...)
{
	int			i;
	t_data		data;

	i = 0;
	ft_init(s, &data);
	va_start(data.ap, s);
	while (data.str[i])
	{
		if (data.str[i] == '%' && data.str[i + 1] == '%')
		{
			ft_putchar(data.str[i], &data);
			i += 2;
		}
		else if (data.str[i] != '%')
			ft_putchar(data.str[i++], &data);
		else if (data.str[i] == '%')
			i = ft_check_string(i + 1, &data);
	}
	return (data.return_printf);
}