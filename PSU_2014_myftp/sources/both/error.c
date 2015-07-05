/*
** error.c for ftp in /home/vadee_s/PSU_2014_myftp/sources/both
** 
** Made by simon vadée
** Login   <vadee_s@epitech.net>
** 
** Started on  Sun Mar 22 10:22:17 2015 simon vadée
** Last update Sun Mar 22 10:22:19 2015 simon vadée
*/

#include <errno.h>
#include "myftp.h"

static const t_error	g_errors[16] =
  {
    {QUIT, "Exited normally after recieving 'quit'"},
    {OK, ""},
    {FAIL_CLOSE, "System error : 'close' failed"},
    {FAIL_LISTEN, "System error : 'listen' failed"},
    {FAIL_BIND, "System error : 'bind' failed"},
    {FAIL_GETPROTOBYNAME, "System error : 'getprotobyname' failed"},
    {FAIL_SOCKET, "System error : 'socket' failed"},
    {FAIL_ACCEPT, "System error : 'accept' failed"},
    {FAIL_CONNECT, "System error : 'connect' failed"},
    {FAIL_MALLOC, "System error : 'malloc' failed"},
    {FAIL_FORK, "System error : 'fork' failed"},
    {FAIL_WRITE, "System error : 'write' failed"},
    {FAIL_OPEN, "System error : 'open' failed"},
    {FAIL_READ, "System error : 'read' failed"},
    {FAIL_FSTAT, "System error : 'fstat' failed"},
    {0, NULL}
  };

int			handle_errors(e_errors error)
{
  int			i;

  i = -1;
  while (g_errors[++i].msg != NULL)
    {
      if (g_errors[i].error == error)
	perror(g_errors[i].msg);
    }
  return 1;
}
