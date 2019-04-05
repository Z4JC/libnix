#include <string.h>
#include <errno.h>
#include "stdio.h"

void perror(const char *string)
{ int err=errno;
  if(string!=NULL)
  { fputs(string,stderr);
    fputc(':',stderr);
    fputc(' ',stderr); }
  fputs(strerror(err),stderr);
  fputc('\n',stderr);
}
