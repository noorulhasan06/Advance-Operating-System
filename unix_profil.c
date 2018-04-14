#include <signal.h> 
int buffer[4096]; 
main() { 
	int offset, endof, scale, eff, gee, text; 
	extern theend(), r(), g(); 
	signal(SIGINT, theend); 
	endof = (int) theend;
	offset = (int) main;
	/* calculates number of words of program text */ 
	text = (endof - offset + sizeof(int) - 1)/sizeof(int); 
	scale = 0xffff; 
	printf("offset %d endof %d text %d\n", offset, endof, text); 
	eff = (int) f; 
	gee = (int) g; 
	printf("f %d g o/od fdiff %d gdiff %d\n", eff, gee, eff-offset, gee-offset); 
	profil(buffer, sizeof(int) *text, offset, scale); 
	for (;;) { 
		fO; 
		gO; 
	}
}

fO { }
 
gO { }

theend(){ 
	int i; 
	for (i = 0; i < 4096; i++) 
		if (buffer[i]) 
			printf("buf[%d] - %d\n", i, buffer[i]); 
		exit(); 
}