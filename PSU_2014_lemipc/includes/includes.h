/*
** includes.h for lemipc in /home/girard_r/rendu/PSU_2014_lemipc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Thu Mar  5 15:26:46 2015 Aurélien GIRARDEAU
** Last update Sun Mar  8 18:57:42 2015 Aurélien GIRARDEAU
*/

#ifndef		INCLUDES_H_
# define	INCLUDES_H_

# define	GUI_CHANNEL		1

# define	DEFINE_TEAM_CHANNEL	2

# define	WIDTH			100
# define	HEIGHT			100

typedef enum
  {
    CREATE = 1,
    MOVE,
    DEAD,
    END
  }		e_cmd;

typedef struct	s_msg_gui
{
  long		mtype;
  e_cmd		cmd;
  int		coord_from[2];
  int		coord_to[2];
  char		team;
}		t_msg_gui;

#endif /* !INCLUDES_H_ */
