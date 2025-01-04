/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hajmoham <hajmoham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:13:01 by hajmoham          #+#    #+#             */
/*   Updated: 2024/08/13 11:13:26 by hajmoham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

ssize_t	ft_putnbr(int num);
ssize_t	ft_putunbr(unsigned int num);
ssize_t	ft_puthex(unsigned long long num, char format);
ssize_t	ft_putchar(char c);
ssize_t	ft_putstr(char *str);
ssize_t	ft_putptr(void *ptr);
ssize_t	handle(va_list args, char format);
ssize_t	ft_printf(const char *format, ...);

#endif
