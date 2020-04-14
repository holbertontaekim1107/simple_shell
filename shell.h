#ifndef SHELL_H
#define SHELL_H
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
char **_strtok(char *line, char *delm);

int _strcmp(char *s1, char *s2);

int _strlen(char *s);

void _strcpy(char *dest, char *src);

int _strncmp(char *s1, char *s2, int n);

int _atoi(char *s);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
#endif
