#ifndef MYLINEUTILS_H
#define MYLINEUTILS

#define MAX_LINESTRLENS 100

int getline_cm(char *line, int maxlen);
int getlines(char input[], int maxinputlen);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

#endif
