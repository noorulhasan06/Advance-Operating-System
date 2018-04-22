#include<fcntl.h>

char string[] = "hello";

void main(int argc, char* argv){
	int fd;
	char buf[256];
	mknod("fifo",010777,0);
	if(argc == 2) fd = open("fifo",O_WRONLY);
	else fd = open("fifo",O_RDONLY);
	for(int i=0; i<64; i++){
		if(argc == 2) write(fd, string, 6);
		else read(fd, buf, 6);
	}
}