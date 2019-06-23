/**
 * C program to use pipe and fork commands of Unix.
 */
#include <string.h> 
#include <stdlib.h>
#include <stdio.h>
char string[] = "hello world"; 
void main() { 
	int count, i; 
	int to_par[2], to_chil[2]; 
	char buf[256]; 
	pipe(to_par); 
	pipe(to_chil); 
	if (fork() == 0) { 
		/* for pipes to parent, child */ 
		/* child process executes here */ 
		close(0); 
		/* close old standard input */ 
		dup(to_chil[0]); 
		/* dup pipe read to standard input */ 
		close(1); 
		/* close old standard output */ 
		dup(to_par[1]); 
		/* dup pipe write to standard out */ 
		close(to_par[1]); 
		/* close unnecessary pipe descriptors */ 
		close(to_chil[0]); 
		close(to_par[0]); 
		close(to_chil[1]); 
		for (;;) { 
			if ((count = read(0, buf, sizeof(buf))) == 0) 
				exit(0);
			printf(" %s %s \n","child",buf); 
			write(1, buf, count); 
		}
	}
	/* parent process executes here */ 
	close(1); 
	/* rearrange standard in, out */ 
	dup(to_chil[1]); 
	close(0); 
	dup(to_par[0]); 
	close(to_chil[1]); 
	close(to_par[0]); 
	close(to_chil[0]); 
	close (to_par[1]); 
	for (i = 0; i < 15; i++) {
		write(1, string, strlen(string));
		read (0, buf, sizeof(buf));
		printf(" %s %s \n","parent",buf); 
	}
}
