/**
	First compile the program : gcc fork_search.cpp
	Second run the program 	  : ./a.out filename(that contains comma seperated integers) number_to_search(eg. 3)
**/
#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

int arr[1024];
int fdtr[2], to_sear=0,size=0;

void search(int s,int e){
  for(int i=s;i<=e;i++){
    if(arr[i] == to_sear){
		   write(fdtr[1],&i,sizeof(i));
		   return;
      }
    }
}

int search_div(int l,int r){
  if(r-l+1 >=5){
    int m = (l+r)/2;
    for(int i=0;i<2;i++){
      int pid = fork();
        if(i==0){
          if(pid==0){
            close(fdtr[0]);
            search_div(l,m);
            close(fdtr[1]);
            return 0;
		  }
		}
        if(i==1){
		     if(pid==0){
		         close(fdtr[0]);
		         search_div(m+1,r);
		         close(fdtr[1]);
		         return 0;
				}
			}
		}
	}
  else search(l,r);
  return 1;
}

void file_to_array(char* filename){
	 FILE *myFile;
    myFile = fopen(filename, "r");
    int i=0;
    if(myFile == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    while(fscanf(myFile, "%d,", &arr[i++]) != EOF);
    size = i-1;
    fclose(myFile);
}

int main(int argc, char* argv[]){
  if(argc !=3) exit(0);
  file_to_array(argv[1]); 
  to_sear = atoi(argv[2]);
  setpgrp();
  pipe(fdtr);
  int i = search_div(0,size-1);
  close(fdtr[1]);
  if(i==0)
    exit(0);
  int index; bool found = false;
  for(;;){
    int r = read(fdtr[0],&index,sizeof(index));
    if(r==0){
      break;
      }
    else{
    	found = true;
    	printf("element found at index: %d.\n",index);		// print all occurences
    }
  }
  if(!found) printf("not found.\n");
}
