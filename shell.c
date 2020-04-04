#include "shell.h"
#include <sys/wait.h>
#include <sys/types.h>

#define NOMEM ("Error: Failed to allocate memory\n")
#define FAILFORK ("Error creating fork\n")
void sigint_handle(int sig);
int _strcmp(char *s1, char *s2);
/**
 * main - A simple shell program
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Program environment
 *
 * Return: Always 0 (ok)
 */
int main(int argc, char *argv[] __attribute__ ((unused)),
	 char *envp[] __attribute__ ((unused)))
{
	size_t n = 1, i = 0;
	char *buff = malloc(1);
	int e = 0, runs = 1, status;
	pid_t pid, w;
	/*When not mallocing, getline alloced too much space. Rely on realloc*/
	(void)argc;
	/*Set SIGINT to default to be caught by the handler*/
	signal(SIGINT, sigint_handle);

	while (1)/*Always true unless exit sent to prompt*/
	{
		write(1, "$ ", 2);
		i = 0;
		if (getline(&buff, &n, stdin) == EOF)
		    return (0);
/*If buff is small, getline reallocs*/
		if (!buff)
			dprintf(STDERR_FILENO, NOMEM), exit(97);
		while (buff[i])
			i++;
		buff[i - 1] = 0;/*getline automatically appends a newline*/
		if (!_strcmp(buff, ""))
			continue;
		if (!_strcmp(buff, "exit"))
			return (0);
		pid = fork();
		if (pid == 0)
		{
			e = execve(buff, argv, envp);
			if (e == -1)
			{
				printf("%s: %d: %s: not found\n", argv[0],
				       runs++, buff);
			}
			return (0);
		}
		else if (pid == -1)
			dprintf(STDERR_FILENO, FAILFORK), exit(99);
		else
		{
			do {
			w = waitpid(pid, &status, WUNTRACED | WCONTINUED);
			if (w == -1)
				perror("Error at waitpid\n"), exit(99);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
		runs++;
	}
	free(buff);
	return (0);
}
/**
 * _strcmp - compares two strings
 *@s1: string 1 to be compared
 *@s2: string 2 to be compared
 * Return: a positive, negative, or 0 number based on the first different char
 */
int _strcmp(char *s1, char *s2)
{
	while ((*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 - *s2);
}
/**
 * sigint_handle - a signal handler for sigint
 * @sig: Caught signal
 *
 * Return: void
 */
void sigint_handle(int sig)
{
	(void)sig;
	signal(SIGINT, sigint_handle);
	printf("\n$ ");
	fflush(stdout);
}
