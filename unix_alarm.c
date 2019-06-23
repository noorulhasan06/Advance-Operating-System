/**
 * C program to illustrate the function of Unix alarm command.
 * This line contains no information.
 */
#include <sys/types.h>
#include <syw/stat.h>
#include <syw/signal.h>
main (argc, argv) int argc; char *argv[]; {
	extern unsigned alarm();
	extern wakeup();
	struct stat statbuf;
	time_t axtime;
	if (argc != 2)	{
		printf("only 1 arg\n");
		exit();
	}
	axtime = (time_t) 0;
	for (;;) { /* find out file access time */
		if (stat(argv[l], &statbuf) == -1) {
			printf("file %s not there\n ", argv[1]);
			exit();
		}
		if (axtime != statbuf.st_atime) {
			printf("file %s accessed\n", argv[1]);
			axtime = statbuf.st_atime;
		}
		signal(SIGALRM, wakeup); /* reset for alarm */
		alarm(60);
		pause(); /* sleep until signal */

	}
}
wakeup() ( }
