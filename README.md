# Simple Shell
A simple UNIX command interpreter written for a low-level programming project at Holberton School.

## About
**hsh** is a simple UNIX command language interpreter that takes commands from files or inputs and executes them.

## Invocation
To use **hsh**: **hsh** [filename]
In order to operate **hsh**, compile all the .c files in the master repository and run the executable: 

	gcc *.c -o hsh
	./hsh

**hsh** can be invoked both interactively and non-interactively. 
I.E:

	**Interactively**
	
	Input: $./hsh
	Output: $

	**Non-Interactively**

	Input: $ echo "echo 'hello world'" | ./hsh
	Output: 'hello world'
	       $
## Command Execution
When **hsh** recieves a command, it will tokenize it into words. The first word is considered the command and the remaining words will be considered arguments to that command. 
**hsh** will then proceed to execute the named program with any remaining given arguments.

i.E:

	Input: $./hsh
	     : $ls
	     : AUTHORS		Shell.c		README.md      	shell.h		_atoi.c
	       strtok.c		.gitignore	_str.c		cd.c		man_1_simple_shell

## Exit

* Usage: exit[status]
* Exits the shell
* If no argument is given to the prompt, the command is taken as exit 0, exiting the hsh.

I.E

	Input: $ exit
	Output:vagrant@vagrant-ubuntu-trusty-64:~$

## Built By
* Tommy Kim
* Brett Davis

## Built With

* [c] - Betty style formatting

### Project contents

| Filename | Short Description |
| --- | --- |
| **hsh** | Simple UNIX command interpreter written by Brett Davis & Tommy Kim |
| .gitignore|Prevents Autosave files from being uploaded|
| AUTHORS   |Authors of this program|
| _atoi.c   |Converts string to integer|
| _str.c    |Contains string functions|
| cd.c      |Change directory program for **hsh**|
| man_1_simpleshell|Manual page for **hsh**|
| shell.c|Main hsh files|
| shell.h |**hsh** header files|
| strtok.c |Function to store data between calls.|
