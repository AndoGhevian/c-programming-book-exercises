#ifndef CHAR_H
#define CHAR_H

/* free buffer related to input.

  warning: MUST be called if
  if input is not exhausted and
  you finish character iteration,
  to eliminate memory leaks.
  */
void flushbuf(char *);
/* reads characters from provided string
  or from standard input if null pointer
  is provided.
  note: If end of input is reached
  (\0 for strings), or input is flushed
  EOF will be returned for subsequent calls.
  */
int getch(char *);
/* unget provded character to
  a buffer tide to this specific
  pointer.
  unget null character for non
  null pointer input, or EOF for
  null pointer is the same as flush.
  note: this is for safety reasons, to not
  accidentally lead to memory leaks,
  in case when you expect you reach
  the end of an input and though
  the buffer is freed.
  */
void ungetch(int, char *);

#endif
