/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:29:44 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/11 15:32:24 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_status(int status)
{
	unsigned char	exit;
	unsigned char	sig;

	exit = status >> 8;
	sig = status;
	if (sig > 0)
		return (128 + sig);
	return (exit);
}
