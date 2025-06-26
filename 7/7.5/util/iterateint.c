int iterateint(int *i, int iend) {
  if(*i == iend)
    return 0;

  if(*i < iend)
    ++*i;
  else
    --*i;

  return 1;
}

/* implement this for documentation purposes */
int iterateint_excluded(int *i, int iend) {
  if(*i == iend || (*i < iend ? ++*i : --*i) == iend)
    return 0;
  return 1;
}
