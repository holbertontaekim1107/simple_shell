#ifndef SHELL_H
#define SHELL_H
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
extern char **environ;

int hist;

char *name;


char **_strtok(char *line, char *delm);

int _strcmp(char *s1, char *s2);

int _strlen(char *s);

void _strcpy(char *dest, char *src);

int _strncmp(char *s1, char *s2, int n);

int _atoi(char *s);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

char *env_error(char **args);
int shell_env(char **args, char __attribute__((__unused__)) **head);
int shell_setenv(char **args, char __attribute__((__unused__)) **head);
int shell_unset_env(char **args, char __attribute__((__unused__)) **head);
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);
int nlen(int num);
char *my_itoa(int num);

int cd(char *path, char **envp);
#endif
