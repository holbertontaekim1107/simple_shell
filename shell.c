#include "shell.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define NOMEM ("Error: Failed to allocate memory\n")
#define FAILFORK ("Error creating fork\n")

int _atoi(char *s);
int fork_exe(pid_t pid, int *runs, char **tok, char **argv, char **envp);
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
int main(int argc, char *argv[], char *envp[])
{
	size_t n = 1;
	char *buff = malloc(1), **tok;
	int runs = 1, i;
	pid_t pid;
	/*When not mallocing, getline alloced too much space. Rely on realloc*/
	(void)argc;
	/*Set SIGINT to default to be caught by the handler*/
	signal(SIGINT, sigint_handle);

	while (1)/*Always true unless exit sent to prompt*/
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		if (getline(&buff, &n, stdin) == EOF)
			return (0);
/*If buff is small, getline reallocs*/
		if (!buff)
			dprintf(STDERR_FILENO, NOMEM), exit(97);
		if (!_strcmp(buff, ""))
			continue;
		tok = _strtok(buff, " ");
		if (!_strcmp(tok[0], "exit"))
		{
			if (_atoi(tok[1]) > 0)
				exit(_atoi(tok[1]));
			else
				return (0);
		}
		pid = fork();
		fork_exe(pid, &runs, tok, argv, envp);
		runs++;
	}
	free(buff);
	free(tok);
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
/**
 * fork_exe - performs an action based on fork pid
 * @pid: pid currently on
 * @runs: number of runs in the shell for error messages
 * @tok: An array of strings containing the tokens
 * @argv: Used for the file name at argv[0]
 * @envp: Program environment
 *
 * Return: 0
 */
int fork_exe(pid_t pid, int *runs, char **tok, char **argv, char **envp)
{
	int e = 0, status;
	pid_t w;

	if (pid == 0)
	{
		e = execve(tok[0], tok, envp);
		if (e == -1)
		{
			printf("%s: %d: %s: not found\n", argv[0],
			       *runs++, tok[0]);
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
	return (0);
}
/**
 * _atoi - converts a string to an integer
 *@s: string to be converted
 * Return: the number after conversion, or 0
 */
int _atoi(char *s)
{
	int i = 0, j, n1, n2, neg = 1, flag = 0;
	unsigned int sum = 0;

	if (s == NULL)
		return (-1);
	while (s[i] != '\0')
		i++;
	for (j = 0, n1 = 0, n2 = 0; j <= i; j++)
	{
		if (s[j] == '-')
		{
			neg *= -1;
			continue;
		}
		else if (s[j] == '+')
		{
			continue;
		}
		else if ((s[j] >= '0') && (s[j] <= '9'))
		{
			if (n1 > n2)
			{
				sum *= 10;
				n2 = n1;
			}
			sum += s[j] - '0';
			flag = 1;
			n1++;
		}
		else if (s[j] == ' ')
			continue;
		else if ((flag == 1) && (!(s[j] >= '0') || !(s[j] <= '9')))
			break;
	}
	return (sum * neg);
}
