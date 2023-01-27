/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msharifi <msharifi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:33:07 by msharifi          #+#    #+#             */
/*   Updated: 2023/01/27 22:22:49 by msharifi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data *data;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data_mem;
	if (data->input.n_meal)
	{
		while (!should_die(data, philo) && philo->meal_count < data->input.n_meal)
			if (life_loop(data, philo))
				return (NULL);
	}
	else
	{
		while (!should_die(data, philo))
			if (life_loop(data, philo))
				return (NULL);
	}
	return (NULL);
}

int	child(t_data *data, t_philo *philo)
{
	if (data->input.n_meal)
	{
		while (!should_die(data, philo) && philo->meal_count < data->input.n_meal)
			if (life_loop(data, philo))
				exit (0);
	}
	else
	{
		while (!should_die(data, philo))
			if (life_loop(data, philo))
				exit (0);
	}
	destroy_semaphore(data);
	exit (1);
}

// Verifie si philo est mort, si oui set data->philo_dead a true
// Return 1 si le philo est mort, sinon 0;
int	should_die(t_data *data, t_philo *philo)
{
	long long	time;

	time = get_time_from_start(philo->t_until_die);
	if (data->philo_dead == true)
		return (1);
	if (time > data->input.to_die)
	{
		data->philo_dead = true;
		sem_wait(data->writing);
		printf("%lld	%d is dead\n", get_time_from_start(data->t_start), philo->pos + 1);
		return (1);
	}
	return (0);
}

int	life_loop(t_data *data, t_philo *philo)
{
	if (pthread_create(&data->thread, NULL, check_dead, philo))
		return (err_msg(TCREAT, 1));
	if (should_die(data, philo))
		return (1);
	if (eating(data, philo))
		return (2);
	if (should_die(data, philo))
		return (1);
	if (sleeping(data, philo))
		return (3);
	if (should_die(data, philo))
		return (1);
	if (thinking(data, philo))
		return (4);
	if (should_die(data, philo))
		return (1);
	pthread_detach(data->thread);
	return (0);
}

void	one_philo(t_data *data)
{
	data->t_start = get_time();
	printf("0	1%s", TAKEN_FORK);
	ft_usleep(data, data->input.to_die);
	printf("%ld	1%s", data->input.to_die, PHILO_DIED);
}
