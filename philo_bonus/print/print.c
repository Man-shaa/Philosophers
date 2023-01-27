/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:32:45 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/27 22:03:37 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	err_msg(char *s1, int ret_val)
{
	if (s1)
	{
		write(STDERR_FILENO, s1, ft_strlen(s1));
		write(STDERR_FILENO, "\n", 1);
	}
	return (ret_val);
}

int	print_action(t_philo *philo, t_data *data, char *action, char *color)
{
	if (should_die(data, philo) || data->philo_dead == true)
		return (1);
	sem_wait(data->writing);
	printf("%lld	%d%s%s"DEFAULT, get_time_from_start(data->t_start),
		philo->pos + 1, color, action);
	sem_post(data->writing);
	return (0);
}
