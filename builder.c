#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <fcntl.h>
#include "readwrite.h"
#include"builder_list.h"
#include <sys/poll.h>
#include <signal.h>
#include <sys/times.h> /* times() */
#include <unistd.h> /* sysconf() */
#define PERMS 0644

char* name_of_pipe(int splitter,int builder)
{
  	char csplitter[100];
	char cbuilder[100];
    char pipe_name[100];
	int keylen;
	char*key;
    sprintf(csplitter,"%d",splitter);	
	sprintf(cbuilder, "%d", builder);
	
    strcat(csplitter,cbuilder);
	
	keylen=strlen(csplitter)+1;
    key = (char*)malloc(keylen * sizeof(char));
	strcpy(key,csplitter);
	
	return key;
	

}




int main(int argc,char** argv)
{
	int i,j,fd;
	int n=0;
  char buffer[100];
	int closed=0;
	int numsplitters=atoi(argv[2]);
   int id=atoi(argv[1]);
builder_List lista=builder_create_list();
	char*pipe_name;

double t1, t2, cpu_time;
struct tms tb1, tb2;
double ticspersec;
int  sum = 0;
ticspersec = (double) sysconf(_SC_CLK_TCK);
t1 = (double) times(&tb1);






struct pollfd pfds[numsplitters];


for (i=0;i<numsplitters;i++){
  	pipe_name=name_of_pipe(i,id);
	
	pfds[i].fd =open(pipe_name, O_RDONLY);
	pfds[i].events = POLLIN;
}

printf("perasa tin loopa twn splitter\n");

int k=0;

while(closed<numsplitters){

int num = poll(pfds, numsplitters, -1);
int ar=0;
if(num != 0)
        {
             if (num == -1)
             {
                 perror("poll");
                 exit(1);
             }

             for(j = 0; j < numsplitters; j++)
             {
                 if(pfds[j].revents & POLLIN)
                 {
					if(read_data (pfds[j].fd ,buffer)>0){
                    
					ar++;
								
					if (strcmp(buffer,"oulala")==0){
						closed++;	

						}
					else{
  	      			if(builder_search_list(lista,buffer)!=1)	
						builder_insert_to_end(lista,builder_create_node(buffer)); 


} }
					        
                 }
             }
         }
}


// teleiwse to diavasma apo tous splitters twra stelnw sto root

pipe_name=name_of_pipe(-1,id);


send_all(lista,pipe_name);



printf("builder %d closed \n",id);


t2 = (double) times(&tb2);
cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) -
(tb1.tms_utime + tb1.tms_stime));
//printf("Run time was %lf sec (REAL time) although we used the CPU for %lf sec (CPU time).\n",(t2 - t1)/ticspersec,cpu_time/ticspersec);
free(pipe_name);
FILE * fpa;
fpa = fopen (argv[3], "a");
fprintf(fpa,"BUILDER %d : (REAL time) %lf sec    (CPU time) %lf sec \n",id,(t2 - t1)/ticspersec,cpu_time/ticspersec);
//sleep(3);
fclose(fpa);
kill(getppid(),SIGRTMIN+2);
kill(getppid(),SIGUSR2);



}
