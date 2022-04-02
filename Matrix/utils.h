#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
char *fgetl(FILE *fp);
int count_fields(char *line);
void malloc_error();
float *parse_fields(char *line, int n);
#endif

