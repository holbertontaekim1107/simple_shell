#include "shell.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define NOMEM ("Error: Failed to allocate memory\n")
#define FAILFORK ("Error creating fork\n")

int path_check(int *runs, char **tok, char **envp, char **argv,
	       char **pathTok);
void free_all(char **s);
int fork_exe(char **tok, char **envp);
void sigint_handle(int sig);
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
	char *buff = malloc(n), **tok = NULL,
		*path = NULL, **ptok = NULL;
	int runs = 1, tmp = 0, p = 0, j = 0;

	(void)argc;
	signal(SIGINT, sigint_handle);

	buff[0] = '\0';
	for (j = 0; envp[j] && _strncmp(envp[j], "PATH=", 4); j++)
		;
	path = malloc(_strlen(envp[j] + 5) + 1);
	_strcpy(path, envp[j] + 5);
	ptok = _strtok(path, ":");
	while (1)/*Always true unless exit sent to prompt*/
	{
		j = 0;
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		if (getline(&buff, &n, stdin) == EOF)
		{
			if (isatty(STDIN_FILENO))
				write(1, "\n", 1);
			break;
		}
		if (!buff)
			write(2, NOMEM, _strlen(NOMEM)), exit(97);
		while (*(buff + j) == ' ')
			j++;
		if (!_strcmp(buff + j, "\n"))
			continue;
		tok = _strtok(buff, " ");
		if (!_strcmp(tok[0], "exit"))/*exit builtin with(out) args*/
			break;
		else if (!_strcmp(tok[0], "cd"))
		{
			cd(tok[1]);
			runs++;
			continue;
		}
		p = path_check(&runs, tok, envp, argv, ptok);
		if (p == -229)
			break;
		runs++;
		free_all(tok);
		tok = NULL;
	}
	if (buff)
		free(buff);
	if (path)
		free(path);
	if (ptok)
		free_all(ptok);
	if (tok)
		if (!_strcmp(tok[0], "exit"))
		{
			if (tok[1] != NULL)
			{
				tmp = _atoi(tok[1]);
				free_all(tok);
				return (tmp);
			}
			else
				free_all(tok);
		}
	return (p);
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
	write(1, "\n$ ", 3);
	fflush(stdout);
}
/**
 * fork_exe - performs an action based on fork pid
 * @tok: An array of strings containing the tokens
 * @envp: Program environment
 * Return: 0
 */
int fork_exe(char **tok, char **envp)
{
	int e = 0, status;
	pid_t pid = fork();

	if (pid == 0)
	{
		e = execve(tok[0], tok, envp);
		exit(e);
	}
	else if (pid == -1)
		write(2, FAILFORK, _strlen(FAILFORK)), exit(99);
	else
	{
		do {
			if (waitpid(pid, &status, WUNTRACED | WCONTINUED) == -1)
				perror("waitpid"), exit(99);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		if (WEXITSTATUS(status) == 255)
			return (-1);
	}
	return (0);
}
/**
 * free_all - frees a char **
 * @s: char ** to be freed
 *
 * Return: void
 */
void free_all(char **s)
{
	int i = 0;

	if (s == NULL)
		return;
	for (; s[i]; i++)
		free(s[i]);
	free(s);
}
/**
 * path_check - determines if program needs to check the path, then checks
 * @runs: Number of runs for the program
 * @tok: tokenized input
 * @envp: program environment
 * @argv: argument vector
 * @pathTok: Tokenized path
 *
 * Return: Always 0
 */
int path_check(int *runs, char **tok, char **envp, char **argv, char **pathTok)
{
	char *path, *fname = malloc(_strlen(argv[0] + 2) + 1);
	char *cname = malloc(_strlen(tok[0]) + 1);
	struct stat buf;
	int i, sflag = 0;

	if (fname == NULL || cname == NULL)
	{
		if (fname)
			free(fname);
		if (cname)
			free(cname);
		write(2, NOMEM, _strlen(NOMEM));
		return (-229);
	}
	_strcpy(fname, argv[0] + 2);
	_strcpy(cname, tok[0]);
	for (i = 0; tok[0][i]; i++)
		if (tok[0][i] == '/')
		{
			sflag = 1;
			break;
		}
	if (sflag == 1)
	{
		if (fork_exe(tok, envp) != 0)
			perror(fname);
	}
	else
	{
		for (i = 0; pathTok[i]; i++)
		{
			path = malloc((_strlen(pathTok[i]) + _strlen(tok[0])
				       + 1 + 1) * sizeof(char));
			if (path == NULL)
				write(2, NOMEM, _strlen(NOMEM)), exit(99);
			_strcpy(path, pathTok[i]);
			path[_strlen(path)] = '/';
			_strcpy(path + _strlen(pathTok[i]) + 1, cname);
			free(tok[0]);
			tok[0] = path;
			if (!stat(tok[0], &buf))
			{
				fork_exe(tok, envp);
				break;
			}
		}
		if (!pathTok[i])
		{
			stat(tok[0], &buf);
			perror(fname);
			free(fname);
			free(cname);
			return (127);
		}
	}
	runs++;
	free(fname);
	free(cname);
	return (0);
}
