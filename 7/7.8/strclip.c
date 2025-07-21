int strclip(char *s, int clipskip, int clipperlen, int cliprest) {
  int cliplen;

  cliplen = 0;
  for(; *s != '\0' && clipskip--; s++);
  for(; *s != '\0' && clipperlen--; s++, cliplen++);
  for(; *s != '\0' && cliprest--; s++);
  if(*s == '\0')
    return 0;

  while(*s++) cliplen++;
  return cliplen;
}
