#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
int count_fields(char *line);
float *parse_fields(char *line, int cols);
char *fgetl(FILE *fp);
#endif