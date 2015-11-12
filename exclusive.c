#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exclusive.h"
#include"splitter.h"

#include"readwrite.h"

#define maximum 30


node* create_node(char*word)
{       
    char* leksi;
	leksi=malloc(maximum*sizeof(char));
	node* komvos;
    komvos=malloc(sizeof(node));
    komvos->next=NULL;
	komvos->previous=NULL;
    strcpy(leksi,word);  
    komvos->word=leksi;
	return komvos;
}



List create_list(void)
{
	List riza=malloc(sizeof(struct root));
       
	riza->First=NULL;
	riza->Last=NULL;
	riza->number=0;
	//printf("created list\n");
	return riza;
}



int insert_to_end(List list,node* nd)
{
        node* komvos;
        if(list->First==NULL)
	{
	
	
	list->First=nd;
	
	
	}
	else
	{
		komvos=list->First;
	while(komvos->next!=NULL)
	{

	komvos=komvos->next;
	}
	nd->previous=komvos;
	komvos->next=nd;
	}
        
        
        list->number++; 
		
	

}

void print_all_from_first(List list)
{
  node* ptr;
  
  if (list->First==NULL)
  	printf("list is empty \n");
  else
   {
    ptr=list->First;
    while (ptr!=NULL)	
    {
     //printf("word=%s\n",ptr->word);
     ptr=ptr->next;
    }		

   } 

}


int search_list(List list,char* word)
{
  node* ptr=NULL;
  
  if (list->First==NULL)
  	printf("list is empty \n");
  else
   {
    ptr=list->First;
    while (ptr!=NULL)	
    {
     if (strcmp(ptr->word,word)==0)
     {
	//printf("there is\n");
        return 1;                        //to vrike
	}
    
     ptr=ptr->next;
    }		

   }
return 0;                    //den to vrike
}



void clean_list(List list)
{
node* ptr;
node* cleaner; 
 
  if (list->First!=NULL)
 {
 
   
    ptr=list->First;
    int ts=0;
    while (ptr!=NULL)	
    {
     
     cleaner=ptr;
     ptr=ptr->next;
     
     ts++;
    
     
     
    
     free(cleaner->word);
     
     free(cleaner);
	
    }		
  }  
    
  free(list);

}


