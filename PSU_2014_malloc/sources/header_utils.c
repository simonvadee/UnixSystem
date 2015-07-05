/*
** header_utils.c for my_malloc in /home/girard_r/rendu/PSU_2014_malloc/sources
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Tue Jan 27 15:45:08 2015 Aurélien GIRARDEAU
** Last update Fri Feb  6 17:37:16 2015 Aurélien GIRARDEAU
*/

#include <stdio.h>
#include "header.h"

t_header		increment_heap(size_t size, t_header last)
{
  t_header		new_header;
  int			cmp;

  cmp = (size + HEADER_SIZE) / getpagesize();
  new_header = sbrk(0);
  if (size == 0 || sbrk(getpagesize() * (cmp + 1)) == (void *)-1)
    {
      return NULL;
    }
  new_header->size = getpagesize() * (cmp + 1) - HEADER_SIZE;
  new_header->is_free = 1;
  new_header->prev = last;
  new_header->next = NULL;
  if (last)
    last->next = new_header;
  split_memory(new_header, size);
  return (new_header);
}

t_header		find_chunk(size_t size, t_header *last)
{
  t_header		tmp;

  tmp = g_base;
  while (tmp)
    {
      *last = tmp;
      if (tmp->size >= size
	  && tmp->is_free == 1)
	{
	  tmp->is_free = 0;
	  return (tmp);
	}
      tmp = tmp->next;
     }
  return (NULL);
}

void			show_alloc_mem()
{
  t_header		tmp;

  tmp = g_base;
  printf("break : %p\n", sbrk(0));
  while (tmp)
    {
      if (tmp->is_free == 0)
	printf("%p - %p : %lu octets\n", (char*)tmp + HEADER_SIZE,
	       (char *)tmp + HEADER_SIZE + tmp->size, tmp->size);
      tmp = tmp->next;
    }
}

size_t			get_four_sup(size_t size)
{
  if (size == 0)
    return (4);
  else if (size % 4 == 0)
    return (size);
  else
    return (size + (4 - size % 4));
}
