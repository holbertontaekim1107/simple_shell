#ifndef SHELL_H
#define SHELL_H
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
char **_strtok(char *line, char *delm);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
#endif
