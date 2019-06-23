/**
 * C program to show usage of Unix time command.
 */
#include<sys/types.h>
#include <sys/times.h>
extern long times();
main() {
	int i;
	/* tms is ciata structure containing the 4 time elements */
	struct tms pb1, pb2;
	long ptl, pt2;
	ptl = times(&pbl);
	for (i = 0; i < 10; i++)
		if (fork() == 0)
			child(i);
	for (i = 0; i < 10; i++)
		wait((int*)0);
	pt2 = times(&pb2);
	printf("parent real %u user %u sys %u cuser %u csys %u\n",
			pt2 - ptl,pb2_tms_utime - pbl.tms_utime, pb2_tms_stime - pbl_tms_stime,
			pb2.tms_cutime - pbl.tms_cutime, pb2.tms_cstime - pbl.tms_cstime);
}

child(int n) {
	int i;
	struct tms cb1, cb2;
	long tl, t2;
	tl = times(&cbl);
	for (i = 0, i < 10000, i++) ;
	t2 = times(&cb2);
	printf("child %d: real %u user %u sys %u\n", n, t2 - tl,
		cb2.tms_utime = cbl.tms_utime, cb2.tms_stime = cbl.tms_stime);
	exit();
}
