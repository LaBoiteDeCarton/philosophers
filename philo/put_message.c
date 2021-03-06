/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_message.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmercadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:57:05 by dmercadi          #+#    #+#             */
/*   Updated: 2022/03/10 15:57:06 by dmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_message(t_phi *phi, char *str)
{
	pthread_mutex_lock(&(phi->data->mx_stdoutaccess));
	if (!phi->data->phi_died)
		printf("%010d    %-4d %s\n", get_time(phi->data->tstart), phi->id, str);
	pthread_mutex_unlock(&(phi->data->mx_stdoutaccess));
}
