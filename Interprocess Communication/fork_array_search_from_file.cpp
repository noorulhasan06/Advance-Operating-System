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

int arr[1024];								/*	array to store values from file.	*/
int fdtr[2], to_sear=0,size=0;

void search(int s,int e){					/*	function to search element from array.	*/
  for(int i=s;i<=e;i++){
    if(arr[i] == to_sear){
		   write(fdtr[1],&i,sizeof(i));		/*	writing the index of the element on pipe.	*/
		   return;
      }
    }
}

int search_div(int l,int r){					
  if(r-l+1 >=5){							// if array size is greater than 5
    int m = (l+r)/2;						// middle of array
    for(int i=0;i<2;i++){					// creating two childrens
      int pid = fork();						// create  child
        if(i==0){							
          if(pid==0){						// first child
            close(fdtr[0]);					// closing read end of pipe
            search_div(l,m);				// do recursive search
            close(fdtr[1]);					// close write end of pipe 
            return 0;
		  }
		}
        if(i==1){
		     if(pid==0){					// second child 
		         close(fdtr[0]);			// close read end 
		         search_div(m+1,r);
		         close(fdtr[1]);			// close write end of pipe 
		         return 0;
				}
			}
		}
	}
  else search(l,r);							// search directly in array 
  return 1;									
}

void file_to_array(char* filename){			// functon reading from file to array 
	 FILE *myFile;
    myFile = fopen(filename, "r");
    int i=0;
    if(myFile == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    while(fscanf(myFile, "%d,", &arr[i++]) != EOF);		// reading to arr 
    size = i-1;								// count of numbers in file 
    fclose(myFile);
}

int main(int argc, char* argv[]){
  if(argc !=3) exit(0);						
  file_to_array(argv[1]); 					// from file to array
  to_sear = atoi(argv[2]);					// element to search 
  setpgrp();								// set the process group ID
  pipe(fdtr);								// create pipe 
  int i = search_div(0,size-1);				// search 
  close(fdtr[1]);							// close write end of pipe 
  if(i==0)
    exit(0);								// exit if child 
  int index; bool found = false;
  for(;;){
    int r = read(fdtr[0],&index,sizeof(index));		// read from file 
    if(r==0){										// break if no writer process 
      break;
      }
    else{
    	found = true;
    	printf("element found at index: %d.\n",index);		// print all occurences
    }
  }
  if(!found) printf("not found.\n");
}
