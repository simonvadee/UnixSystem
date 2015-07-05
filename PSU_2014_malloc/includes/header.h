/*
** header.h for header in /home/girard_r/rendu/PSU_2014_malloc/includes
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Tue Jan 27 15:32:19 2015 Aurélien GIRARDEAU
** Last update Fri Feb  6 18:15:28 2015 Aurélien GIRARDEAU
*/

#ifndef HEADER_H_
# define HEADER_H_

# include <stddef.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

# define HEADER_SIZE		32
# define MIN(x, y)		((x >= y) ? y : x)

struct				s_header
{
  size_t			size;
  int				is_free;
  struct s_header		*next;
  struct s_header		*prev;
};

typedef struct s_header 	*t_header;

void				*malloc(size_t size);
void				free(void *ptr);
t_header			increment_heap(size_t size, t_header last);
t_header			find_chunk(size_t size, t_header *last);
void				show_alloc_mem();
void				*realloc(void *ptr, size_t taille);
size_t				get_four_sup(size_t size);
void				*calloc(size_t, size_t);
void				split_memory(t_header toSplit, size_t size);
void				fusion(t_header ptr);
int				valid(void *ptr);
t_header			get_block_addr(void *ptr);

extern t_header			g_base;
extern pthread_mutex_t		g_mutex;

#endif /* !HEADER_H_ */
