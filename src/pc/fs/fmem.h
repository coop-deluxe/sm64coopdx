#ifndef FMEM_H
#define FMEM_H

#include <stdio.h>

FILE   *f_open_r   (const char *filename);
FILE   *f_open_w   (const char *filename);
int     f_close    (FILE *f);
void    f_delete   (FILE *f);
size_t  f_read     (void *dst, size_t size, size_t count, FILE *f);
size_t  f_write    (const void *str, size_t size, size_t count, FILE *f);
int     f_seek     (FILE *f, long offset, int origin);
long    f_tell     (FILE *f);
void    f_rewind   (FILE *f);
int     f_flush    (FILE *f);
void    f_shutdown ();

#endif
