#include<stdio.h>
#include<string.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include "exclusive.h"
#include "splitter.h"
#include <signal.h>


int main(int argc,char** argv)
{
	
	char ch;         //elenxw xaraktira xaraktira me tin fgetc	
	FILE * fp;
	char buffer[100]; //o buffer ston opoio apothikeuete kathe leksi
	int i=0;		//index tou buffer
	int count=0;    
	int grammes=atoi(argv[1]); //poses grammes tha diavasei o splitter
	int offset=atoi(argv[2]);  //apo pou tha arxisei na diavazei o splitter
	char filename[100];	
	char exclusivefile[100];
	int n=0;					//counter gia to poses grammes exoun diavastei mexri tr
	char *pipe_name;
	int fd;
	mode_t fdmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH ;
	char buf[1024];
	strcpy(filename,argv[3]);   // apo pio arxeio diavazoume
	strcpy(exclusivefile,argv[4]) ;   // to onoma toy exclusive arxeiou
	int m=atoi(argv[5]);    //arithmos builders
	List exclusive;
	//printf("splitter %s\n",argv[6]);
	int l=atoi(argv[7]);
	//pipe_name=name_of_pipe(atoi(argv[6]),2);
	//printf("to onoma t arxeiou einai %s\n",pipe_name);
	exclusive=create_list();	
   	insert_word_to_list(exclusivefile,&exclusive);
	//pipe_name=name_of_pipe(argv[6],1);
	
	
	//print_all_from_first(exclusive);
   fp = fopen (filename,"r");  
   if (fp == NULL)
   {
		printf ("Error opening file unexist.ent: %s\n",strerror(errno));
		exit(10);
   }
   
	if(fseek(fp,offset,SEEK_SET)==-1)
		printf("error fseek: %s\n",strerror(errno)); 
   int coula=0;
	while( ( ch = fgetc(fp) ) != EOF )
    {         
		if ((ch>65 && ch<91)|| (ch >96 && ch<123))   //diavazw gramma gramma kai an einai xaraktiras ton vazw ston buffer
		{	
			if (ch >65 && ch<91)   //ean einai kefalaia metatrepse ta se mikra
				ch=lower_to_upper(ch);
			buffer[i++]=ch;
		}
		else
		{
			buffer[i++]='\0';                       //an dn einai xaraktiras to epomeno  vazw sto telos t buffer  \0 na dilwsw
			i=0;									//oti einai leksi
			if ((buffer[0]>65 && buffer[0]<91)|| (buffer[0] >96 && buffer[0]<123))//ean to prwto tou buffer einai xaraktiras exoume leksi
			{	
				if (search_list(exclusive,buffer)==0)
				{	
					pipe_name=name_of_pipe(atoi(argv[6]),sfold(buffer,m));
								
					
					//printf("to onoma t arxeiou einai %s\n",name_of_pipe(argv[6],1));
					if ( ( fd = open (pipe_name, O_WRONLY | O_CREAT | O_APPEND  , fdmode )) < 0 ) 
					{
						perror ( " open fgfgrgrgr" ); exit (1) ; 



					}	
					
					coula++;
					if (coula==1)
					{printf("splitter %s first word is %s\n",argv[6],buffer);}

					write_data ( fd,buffer);
					close(fd);		
					//write(fd, buffer, strlen(buffer));
					//printf("%s\n",buffer);
					//printf("hash give %ld\n",sfold(buffer, m));

				count++;}	
			}
		}  
 
		if(ch=='\n')
		{                                       //exoume alli mia grammi  auksanete o n otan mexri na ftasoume ston katalailo aithmo
			n++;
			//printf("to l einai %d\n",l);
			if (n==grammes && l!=(atoi(argv[6])+1) )   //ean  einai o teleutaios splitter diavazei mexri to telos
				break;		
		}
	}
		printf("o splitter %s diavase %d grammes\n",argv[6],n);
	for (i=0;i<m;i++)
	{		pipe_name=name_of_pipe(atoi(argv[6]),i);
			if ( ( fd = open (pipe_name, O_WRONLY | O_CREAT | O_APPEND  , fdmode )) < 0 ) 
					{
						perror ( " open   22222222 " ); exit (1) ; 
					}
			write_data ( fd,"oulala");
			
	}


	///write_data ( fd,"oulala");
    //printf ("oi grammes einai %d\n",n);
	//printf("to count einai %d\n",count); //metraei tis lekseis
	fclose(fp);
	clean_list(exclusive);
	printf("teleiwse o splitter\n");
	kill(getppid(),SIGRTMIN+1);
	kill(getppid(),SIGUSR1);
	free(pipe_name);
	return 0;

}





