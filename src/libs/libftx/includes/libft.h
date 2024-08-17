/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 14:33:51 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/17 02:24:44 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <ft_defines.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <math.h>

# include <ft_colors.h>
# include <ft_enums.h>
# include <ft_structs.h>

# include <ft_char.h>
# include <ft_convert.h>
# include <ft_file.h>
# include <ft_gnl.h>
# include <ft_int.h>
# include <ft_lists.h>
# include <ft_math.h>
# include <ft_mem.h>
# include <ft_printf.h>
# include <ft_pthread.h>
# include <ft_str.h>
# include <ft_structs.h>
# include <ft_unistd.h>
# include <ft_system.h>

// First of all you need to check @link `t_var` in ft_structs.h

/**
 * @brief General purpose Cleanup funcion
 * @param var gobal variable
 * @param doexit if the function should use `exit` or not
 * @param statuscode status code of the `exit` call.
 * @attention the library doesn't have an implementation of this function.
 * Create one when using `t_var` it in your project.
 */
int		cleanup(t_var *var, bool doexit, int statuscode);

/**
 * @brief Check whether libft was compiled in debug mode or not.
 * @return `true` if it is, `false` otherwise.
 */
bool	ft_isdebug(void);

#endif