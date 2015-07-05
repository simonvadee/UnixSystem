/*
** parse_entry.c for philo in /home/girard_r/rendu/PSU_2014_philo
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Mar  1 19:43:40 2015 Aurélien GIRARDEAU
** Last update Sun Mar  1 21:08:27 2015 Aurélien GIRARDEAU
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "philo.h"

int			set_informations(t_chopstick **sticks,
					 t_philosopher **philo, t_infos *data)
{
  unsigned int		i;

  i = 0;
  while (i != data->nb_philo)
    {
      (*sticks)[i].id = i;
      pthread_mutex_init(&((*sticks)[i].handler), NULL);
      ++i;
    }
  i = 0;
  while (i != data->nb_philo)
    {
      (*philo)[i].id = i;
      (*philo)[i].which = NONE;
      (*philo)[i].state = REST;
      (*philo)[i].rice = data->rice;
      (*philo)[i].tab = *sticks;
      (*philo)[i].data = data;
      if (pthread_create(&((*philo)[i].instance),
			 NULL, philo_routine, &((*philo)[i])))
	return (-1);
      ++i;
    }
  return 0;
}

int		default_settings(t_chopstick **sticks, t_philosopher **philo)
{
  t_infos	*data;

  if ((*sticks = malloc(sizeof(t_chopstick) * 7)) == NULL
      || (*philo = malloc(sizeof(t_philosopher) * 7)) == NULL
      || (data = malloc(sizeof(t_infos))) == NULL)
    return (-1);
  data->nb_philo = 7;
  data->rice = 10;
  data->time_eating = 1;
  data->time_thinking = 1;
  if (data->nb_philo == 7 && init_sdl() != 0)
    return (-1);
  return (set_informations(sticks, philo, data));
}

int		ask_questions(t_infos *data, char *buff)
{
  int 		tmp;

  printf("Sure, let's go. How many philosophers do you want ?\n");
  if ((tmp = read(0, buff, 512)) == -1)
    return (-1);
  buff[tmp - 1] = 0;
  data->nb_philo = atoi(buff);
  printf("Ok. How many grain of rice do I give to each philosopher ?\n");
  if ((tmp = read(0, buff, 512)) == -1)
    return (-1);
  buff[tmp - 1] = 0;
  data->rice = atoi(buff);
  printf("And for how long must a philosopher eat \
? (we are talking seconds here, minimum one)\n");
  if ((tmp = read(0, buff, 512)) == -1)
    return (-1);
  buff[tmp - 1] = 0;
  data->time_eating = atoi(buff);
  printf("Good. Same question for the thinking now. (minimum one)\n");
  if ((tmp = read(0, buff, 512)) == -1)
    return (-1);
  buff[tmp - 1] = 0;
  data->time_thinking = atoi(buff);
  return (0);
}

int		custom_settings(t_chopstick **sticks, t_philosopher **philo)
{
  char		*buff;
  t_infos	*data;

  if ((buff = malloc(sizeof(char) * 512)) == NULL
      || (data = malloc(sizeof(t_infos))) == NULL)
    return (-1);
  else if (ask_questions(data, buff) == -1)
    return (-1);
  free(buff);
  if (data->nb_philo == 0
      || (*sticks = malloc(sizeof(t_chopstick) * data->nb_philo)) == NULL
      || (*philo = malloc(sizeof(t_philosopher) * data->nb_philo)) == NULL
      || data->time_eating < 1
      || data->time_thinking < 1
      || data->nb_philo == 7 && init_sdl() != 0)
    {
      free(data);
      return (-1);
    }
  printf("Fine ! We're all set. I guess they should be able \
to resolve the starvation in the world now.\n");
  return (set_informations(sticks, philo, data));
}

int		parse_entry(t_chopstick **sticks, t_philosopher **philo)
{
  char		*buff;
  int		ret;

  if ((buff = malloc(sizeof(char) * 512)) == NULL)
    return (-1);
  printf("Would you like to configure the settings ? \
Otherwise I'll do it myself. (y/n)\n");
  while ((ret = read(0, buff, 512)) > 0)
    {
      buff[ret - 1] = 0;
      if (strcmp(buff, "n") == 0)
	{
	  free(buff);
	  return (default_settings(sticks, philo));
	}
      else if (strcmp(buff, "y") == 0)
	{
	  free(buff);
	  return (custom_settings(sticks, philo));
	}
      else
	printf("Do not mess with me. I said y or n.\n");
    }
  return (-1);
}
