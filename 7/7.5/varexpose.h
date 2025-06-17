#ifndef VAREXPOSE_H
#define VAREXPOSE_H
/* in the future it will be good to implement different types
for exposure, like "&i1 &f2 &7-&f10" and so on. */
enum expose_types {
  EXPOSE_FLOAT
};

struct varexpose {
  int i;
  int type;
  struct varexpose *next;
};

struct varexpose *parse_varexposeconfig(char const *conf);

enum varexpose_error {
  OK_VAR_EXPOSE,
  UNABLE_ALLOCATE_VAR_EXPOSE_MEMORY,
  INVALID_VAR_EXPOSE_CONFIG,
  INVALID_VAR_RANGE_EXPOSE_END_CONFIG
};

enum varexpose_error varexp_errno;
char const *varexp_errstr;

static char *varexp_err_messages[] = {
  "", /* 0 -> no error */
  "unable to allocate memory for configuration entity data structure",
  "invalid expose configuration entity",
  "invalid variable range expose configuration end"
};

#endif
