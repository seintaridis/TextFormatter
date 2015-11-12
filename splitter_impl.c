#include "exclusive.h"
//#include "splitter.h"
#include<stdio.h>
#include<string.h>
#include <errno.h>
#include <stdlib.h>




char *substring(char *string, int position, int length) 
{
   char *pointer;
   int c;
 
   pointer = malloc(length+1);
 
   if (pointer == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(EXIT_FAILURE);
   }
 
   for (c = 0 ; c < position -1 ; c++) 
      string++; 
 
   for (c = 0 ; c < length ; c++)
   {
      *(pointer+c) = *string;      
      string++;   
   }
 
   *(pointer+c) = '\0';
 
   return pointer;
}

long sfold(char* s, int M) {
  int intLength = strlen(s) / 4;
  long sum = 0;
  char c[100];
int j;
  for ( j = 0; j < intLength; j++) {
    strcpy(c, substring(s,j * 4, (j * 4) + 4));
    long mult = 1;
	int k;
    for ( k = 0; k < strlen(c); k++) {
      sum += c[k] * mult;
      mult *= 256;
    }
  }

  strcpy(c, substring(s,intLength * 4,strlen(s)));
  long mult = 1;
	int k;
  for ( k = 0; k < strlen(c); k++) {
    sum += c[k] * mult;
    mult *= 256;
  }

  return(abs(sum) % M);
}




char lower_to_upper(char c)
{
       c=c+32;
	   return c;
}


insert_word_to_list(char* filename,List* list)
{
	printf("%s\n",filename);
	char ch;
	int i=0;
	int count=0;
	char buffer[100];
	FILE* fp;
	fp = fopen (filename,"r");  
   if (fp == NULL)
   {
		printf ("Error opening file unexist.ent: %s\n",strerror(errno));
		exit(15);
   }
   
	
   
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
				//printf("%s\n",buffer);
				insert_to_end(*list,create_node(buffer));
				count++;
				//printf("count =%d\n",count);	
			}
		}  
 
		
	}

	//printf("to count einai %d\n",count); //metraei tis lekseis
	fclose(fp);



}



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


