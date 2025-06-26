enum var_entities {
  INVALID_VAR_STR,
  SINGLE_VAR,
  VAR_RANGE
};

/*format: it is assumed there is no spaces,
valid formats single "&dd", range: "&dd...&dd", "...&dd"
and optional rest string part */
enum var_entities parse_varstr(char const *, int *, int *, char *);
