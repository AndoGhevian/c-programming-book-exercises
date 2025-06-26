/* return value of var of provided index or 0.0. */
float lookupvar(int);

/* accept index and value of a var and try to install.
  0 returned if unable to perform operation.
*/
int installvar(int, float);

/* return next var index installed.
  to start scanning you can pass anything
  less than or equal to 0.
  -1 returned if end is reached.
*/
int scanvar(int);

void free_vartable(void);
