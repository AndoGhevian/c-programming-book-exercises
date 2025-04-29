#ifndef KEYVAL_H
#define KEYVAL_H

struct keyval { char *key; int value; };

struct keyval *binsrch_keyval(char *, struct keyval *, int);

#endif
