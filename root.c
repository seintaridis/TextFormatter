#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "readwrite.h"
#include"exclusive.h"
#include "splitter.h"
#include <sys/poll.h>
#include <fcntl.h>
#include "builder_list.h"
#include "signal.h"
#include <sys/times.h> /* times() */
#include <unistd.h> /* sysconf() */

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

int signals_received_builder=0;
int signals_received_splitter=0;
int signals_received_builder_bonus=0;
int signals_received_splitter_bonus=0;
void sig_handler(int signo)
{
	//printf("Root got:%d\n",signo);
	if(signo==SIGUSR2) signals_received_builder++;
	if(signo==SIGUSR1) signals_received_splitter++;
	if(signo==SIGRTMIN+2) signals_received_builder_bonus++;
	if(signo==SIGRTMIN+1) signals_received_splitter_bonus++;
}









int main (int argc, char** argv) 
{       

int flagi=0;
int flagl=0;
int flagm=0;
int flagt=0;
int flage=0;
int flago=0;
int argu=0;
char textfile[30];
char exlusionlistfile[30];
char outputfile[30];
char loadbuf[30];
char buf[30];
char numofsplitter[30];
char numofbuilder[30];
char *pipe_name;
int m,l,top,i,pid,j,closed;
int d;
int lpb=0;    //lines per builder
int lines=0;
long offset=0;
int counteras=0;
char ch;
char numoflines[30];
char buffer[30];
char buffer1[30];
int splitter_lines;
FILE* fp;
double t1, t2, cpu_time;
struct tms tb1, tb2;
double ticspersec;
int  sum = 0;
ticspersec = (double) sysconf(_SC_CLK_TCK);
t1 = (double) times(&tb1);

/*Instaling signal handler*/
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa,NULL) == -1) {
		perror("sigaction");
		return -1;
    }
    if (sigaction(SIGUSR2, &sa,NULL) == -1) {
		perror("sigaction");
		return -1;
    }
	if (sigaction(SIGRTMIN+1, &sa,NULL) == -1) {
		perror("sigaction");
		return -1;
    }
	if (sigaction(SIGRTMIN+2, &sa,NULL) == -1) {
		perror("sigaction");
		return -1;
    }






while ((d = getopt(argc, argv, "ilmteo:")) != -1)
        switch (d)
    {
        case 'i':
            flagi=1;
            argu = argu+2;
            strcpy(textfile,argv[argu]);
            printf("TextFile:%s\n",textfile);
			break;
        case 'l':
            flagl=1;
            argu = argu+2;
            strcpy(numofsplitter,argv[argu]);
			l=atoi(numofsplitter);
            printf("numOfSplitter:%s\n",numofsplitter);
            break;
        case 'm':
			flagm=1;
			argu = argu+2;
            strcpy(numofbuilder,argv[argu]);
			m=atoi(numofbuilder);
            printf("numOfBuilders:%s\n",numofbuilder);
            break;
		case 't':
			flagt=1;
			argu = argu+2;
            strcpy(loadbuf,argv[argu]);
			top=atoi(loadbuf);
            printf("TopPopular:%d\n",top);
            break;
		case 'e':
            flage=1;
            argu = argu+2;
            strcpy(exlusionlistfile,argv[argu]);
            printf("ExclusionList:%s\n",exlusionlistfile);
			break;
		case 'o':
            flago=1;
            argu = argu+2;
            strcpy(outputfile,argv[argu]);
            printf("OutputFile:%s\n",outputfile);
			break;
            //strcpy(config_file_path, buf);
            //memset(buf,0,sizeof(buf));
            break;
        default:
            break;
    }
   
      
   



	fp = fopen (textfile,"r");  
   	if (fp == NULL)
   	{
		printf ("Error opening file unexist.ent: %s\n",strerror(errno));
		exit(13);
   }
	
	
	




	
	if( fgets (buf, 60, fp)!=NULL ) {
     lines=atoi(buf);                             //diavazw tin prwth seira t arxeiou gia na mathw poses grammes exw
      //printf("oi grammes tou arxeiou einai %d \n",lines);
   }
    splitter_lines=lines/l;          //ipologizw tis grammes p tha diavasei o kathe splitter
	sprintf(numoflines, "%d", splitter_lines);
	
	offset=ftell(fp);               //dinw to offset oste na diavazei meta tin prwth grammi
	sprintf(buf, "%lu", offset);
	


	for (i=0;i<l;i++)								//dimiourgw se autin tin loopa ta pipes splitter builder
	{
		//printf ("mpika\n");
		for(j=0;j<m;j++)
		{
			
			pipe_name=name_of_pipe(i,j);
			if ( mkfifo ( pipe_name , 0666) < 0)
			{
				perror ( " Error creating the named pipe " );
				exit (1);
			}
	        free(pipe_name);
			//printf("to onoma tou pipe einai %s\n",pipe_name);
		}
	}

	for (i=0;i<m;i++)								//dimiourgw se autin tin loopa ta pipes  builder root
	{
		pipe_name=name_of_pipe(-1,i);
		if ( mkfifo ( pipe_name , 0666) < 0)
		{
			perror ( " Error creating the named pipe " );
			exit (1);
		}
	free(pipe_name);
	}



      	
		
	printf("SPLITTER LINES IS  %d\n",splitter_lines);	
	for(i = 0; i<l; i++) 
	{
		counteras=0;
        if (i>0)
		{
		while( ( ch = fgetc(fp) ) != EOF )
		{
			if(ch=='\n')
				{                                       //exoume alli mia grammi  auksanete o n otan mexri na ftasoume ston katalailo a  
				counteras++;	
				if (counteras==splitter_lines)
					break;
				}
		}
		offset=ftell(fp);               //dinw to offset oste na diavazei meta tin prwth grammi
	    sprintf(buf, "%lu", offset);		



		}
    	pid = fork();
    	if(pid < 0) 
		{
        	printf("Error");
        	exit(1);
    	} 
		else if (pid == 0) 
		{
            
            
			int aInt = i;
			char str[15];
			sprintf(str, "%d", aInt);
        	//printf("Child (%d): %d\n", i + 1, getpid());   //to str einai pios splitter kaleite
			char *execArgs[] = { "./splitter",numoflines,buf,textfile,exlusionlistfile,numofbuilder,str,numofsplitter,NULL };//to ena einai 
			int x=execvp(execArgs[0], execArgs);
			if (x==-1)
				perror("execvp:\n");        	
			exit(0); 
    	}
		else  
		{
       // wait(NULL); 
		
    	}
}
		for (i=0;i<m;i++)
		{
				pid = fork();
    			if(pid < 0) 
				{
        			printf("Error");
        			exit(1);
    			} 
				else if (pid == 0) 
				{			
				    int ts = i;
					char str1[15];
					sprintf(str1, "%d", ts);    //oste na kserei o builder pios einai

					
					char* execArgs1[] = { "./builder",str1,numofsplitter,outputfile,NULL };//to ena einai 
					int y=execvp(execArgs1[0], execArgs1);
					
				}	
				else  
				{int status;
				//wait(&status);
			       			
			    //wait(NULL); 
		
    			}

		}
		





    
		builder_List lista=builder_create_list();
		struct pollfd pfds[m];
		

for (i=0;i<m;i++){
  	pipe_name=name_of_pipe(-1,i);
	//printf("to onoma einai fdsgfdgfdgd %s\n",pipe_name);
	pfds[i].fd =open(pipe_name, O_RDONLY);
	pfds[i].events = POLLIN;
	free(pipe_name);
}
//printf("TO CLOSED EINAI %d\n",closed);



closed=0;
while(closed<m){


int num = poll(pfds, m, -1);

if(num != 0)
        {
             if (num == -1)
             {
                 perror("poll");
                 exit(1);
             }

             for(j = 0; j < m; j++)
             {
                 if(pfds[j].revents & POLLIN)
                 {
					if(read_data (pfds[j].fd ,buffer)>0){
                     //read the written pipe
					//printf("eimai edw\n");
					//printf("%s\n",buffer);
					read_data (pfds[j].fd ,buffer1);
								
					if (strcmp(buffer,"oulala")==0){
						closed++;	

						}
					else{
  	      				builder_insert_to_end(lista,builder_create_node1(buffer,buffer1)); 
						} }
					        
                 }
             }
         }
}

for (i=0;i<l*m;i++)  
		wait(NULL);

	builder_node* node=lista->First;
	MergeSort(&lista->First);
	builder_print_all_from_first(lista,outputfile);
	builder_print_all_from_first1(lista,"dataforplot",top);
	builder_clean_list(lista);
	//sleep(5);
	
for (i=0;i<l;i++)								//diagrafw se autin tin loopa ta pipes splitter builder
	{
		//printf ("mpika\n");
		for(j=0;j<m;j++)
		{
			
			pipe_name=name_of_pipe(i,j);
			unlink(pipe_name);
	
			//printf("to onoma tou pipe einai %s\n",pipe_name);
			free(pipe_name);		
		}
	
	}
	
for (i=0;i<m;i++){	
	pipe_name=name_of_pipe(-1,i);
	unlink(pipe_name);
		free(pipe_name);}
  //unlink("00");
  

FILE * fpa;
fpa = fopen (outputfile, "a");

fprintf(fpa,"ta simata SIGUSER2: %d\n",signals_received_builder);
fprintf(fpa,"ta simata SIGUSER1: %d\n",signals_received_splitter);
fprintf(fpa,"ta simata SIGRTMIN+2: %d\n",signals_received_builder_bonus);
fprintf(fpa,"ta simata SIGRTMIN+1: %d\n",signals_received_splitter_bonus);
printf("ta simata SIGUSER2: %d\n",signals_received_builder);
printf("ta simata SIGUSER1: %d\n",signals_received_splitter);
printf("ta simata SIGRTMIN+2: %d\n",signals_received_builder_bonus);
printf("ta simata SIGRTMIN+1: %d\n",signals_received_splitter_bonus);
t2 = (double) times(&tb2);
cpu_time = (double) ((tb2.tms_utime + tb2.tms_stime) -
(tb1.tms_utime + tb1.tms_stime));

fprintf(fpa,"ROOT: (REAL time) %lf sec    (CPU time) %lf sec \n",(t2 - t1)/ticspersec,cpu_time/ticspersec);
//sleep(3);
fclose(fpa);
fclose(fp);	

pid=fork();
if (pid==0)
{char* execArgs2[] = { "gnuplot","script",NULL };//to ena einai 
int tsara=execvp(execArgs2[0], execArgs2);
}



}
