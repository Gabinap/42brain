/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gagulhon <gagulhon@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 15:51:19 by gagulhon          #+#    #+#             */
/*   Updated: 2025/11/30 20:18:20 by gagulhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include <stdarg.h>
# include <unistd.h>

va_list	*whilenotpercent(char *s);
int		ft_printf(const char *s, ...);
int		ft_putstr_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);

#endif
