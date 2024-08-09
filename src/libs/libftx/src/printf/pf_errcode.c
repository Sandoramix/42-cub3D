/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_errcode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 08:23:24 by odudniak          #+#    #+#             */
/*   Updated: 2024/08/09 14:05:30 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	errswitch2(t_errorcode code)
{
	if (code == E_MLX)
		return (ft_perror("Failed minilibx connection."));
	if (code == E_MLXWIN)
		return (ft_perror("Failed minilibx window creation."));
	if (code == E_MLXIMG)
		return (ft_perror("Failed minilibx image creation."));
	return (ft_perror("."));
}

static int	errswitch(t_errorcode code)
{
	if (code == E_MALLOC)
		return (ft_perror("Malloc allocation failed."));
	if (code == E_INVALID_ARGC)
		return (ft_perror("Invalid number of arguments."));
	if (code == E_FILE_NOT_FOUND)
		return (ft_perror("File not found."));
	if (code == E_FILE_PERMISSION_DENIED)
		return (ft_perror("File permissions denied."));
	if (code == E_ENV_LOAD)
		return (ft_perror("Failed loading ENV variables."));
	if (code == E_PATH_LOAD)
		return (ft_perror("Failed loading \"PATH\" from env."));
	if (code == E_FORK)
		return (ft_perror("Fork failure."));
	if (code == E_PIPE)
		return (ft_perror("Pipe failure."));
	if (code == E_DUP2 || code == E_DUP)
		return (ft_perror("Dup%c failure.",
				(char [2]){'2', '\0'}[code == E_DUP]));
	if (code == E_EXECVE)
		return (ft_perror("Execve failure."));
	if (code == E_SYNTAX)
		return (ft_perror("Syntax error."));
	return (errswitch2(code));
}

int	pf_errcode(t_errorcode code)
{
	int	len;

	len = ft_perror("[Error]");
	if (code != E_DEFAULT)
		len += ft_perror(":\t") + errswitch(code);
	return (len + ft_perror("\n"));
}
