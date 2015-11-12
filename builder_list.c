#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builder_list.h"
#include <fcntl.h>
#define maximum 30


builder_node* builder_create_node(char*word)
{       
    char* leksi;
	leksi=malloc(maximum*sizeof(char));
	builder_node* komvos;
    komvos=malloc(sizeof(builder_node));
    komvos->next=NULL;
	komvos->previous=NULL;
	komvos->f=1;
    strcpy(leksi,word);  
    komvos->word=leksi;
	return komvos;
}

builder_node* builder_create_node1(char*word,char* sixnotita)
{       
    char* leksi;
	leksi=malloc(maximum*sizeof(char));
	builder_node* komvos;
    komvos=malloc(sizeof(builder_node));
    komvos->next=NULL;
	komvos->previous=NULL;
	komvos->f=atoi(sixnotita);
    strcpy(leksi,word);  
    komvos->word=leksi;
	return komvos;
}




builder_List builder_create_list(void)
{
	builder_List riza=malloc(sizeof(struct builder_root));
       
	riza->First=NULL;
	riza->Last=NULL;
	riza->number=0;
	
	return riza;
}



int builder_insert_to_end(builder_List list,builder_node* nd)
{
        builder_node* komvos;
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

void builder_print_all_from_first(builder_List list,char *filename)
{
FILE * fp;

   fp = fopen (filename, "a");
	fprintf(fp,"LEXANA ANALYSIS \n");
  builder_node* ptr;
  
  if (list->First==NULL)
  	printf("list is empty \n");
  else
   {
    ptr=list->First;
    while (ptr!=NULL)	
    {
	
   fprintf(fp, "%9.9s \t %d\n",ptr->word,ptr->f );
   
   
     
		
     ptr=ptr->next;
    }		

   }
fclose(fp); 
  printf("the number of words in builder is %d\n",list->number);
}

void builder_print_all_from_first1(builder_List list,char *filename,int k)
{
FILE * fp;
int count=0;
   fp = fopen (filename, "w");
	fprintf(fp,"THE TOP %d WORDS\n",k);
  builder_node* ptr;
  
  if (list->First==NULL)
  	printf("list is empty \n");
  else
   {
    ptr=list->First;
    while (ptr!=NULL)	
    {
	count++;
   fprintf(fp, "%9.9s \t %d\n",ptr->word,ptr->f );
   
   
     
	 if (count==k)
	{
		fclose(fp); 
		return;
}
     ptr=ptr->next;
    }		

   }
fclose(fp); 
  
}





void send_all(builder_List list,char* pipe_name)
{
  builder_node* ptr;
int fd;
	mode_t fdmode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH ;
	
  if ( ( fd = open (pipe_name, O_WRONLY | O_CREAT | O_APPEND  , fdmode )) < 0 ) 
					{
						perror ( " open " ); exit (1) ; 
					}
	
  if (list->First==NULL)
  	printf("list is empty \n");
  else
   {
    ptr=list->First;
    while (ptr!=NULL)	
    {
		
		int aInt = ptr->f;
		char str[15];
		sprintf(str, "%d", aInt);
		//printf("stelnw tin leksi %s\n",ptr->word);
		//printf("sixnotita %s\n",str);
		write_data(fd,ptr->word);
		write_data(fd,str);
     //printf("word=%s and frequence is %d \n",ptr->word,ptr->f);
		
     ptr=ptr->next;
    }		
	write_data(fd,"oulala");
	write_data(fd,"-3");
   } 
  //printf("the number of words in builder is %d\n",list->number);
}








int builder_search_list(builder_List list,char* word)
{
  builder_node* ptr=NULL;
  
  if (list->First==NULL)
  	return 0;			// i lista einai adeia
  else
   {
    ptr=list->First;
    while (ptr!=NULL)	
    {
     if (strcmp(ptr->word,word)==0)
     {
	    ptr->f++;                            // an iparxei i leksi apla auksanoume tin sixnotita
        return 1;                        //to vrike
	}
    
     ptr=ptr->next;
    }		

   }
return 0;                    //den to vrike
}



void MergeSort(builder_node** list)
{
  builder_node* head = *list;
  builder_node* a;
  builder_node* b;
	if ((head == NULL) || (head->next == NULL))
  {
    return;
  }
	FrontBackSplit(head, &a, &b); 
 
  /* Recursively sort the sublists */
  MergeSort(&a);
  MergeSort(&b);
 
  /* answer = merge the two sorted lists together */
  *list = SortedMerge(a, b);






}


builder_node* SortedMerge(builder_node* a, builder_node* b)
{
	builder_node* result = NULL;
	if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);
if (a->f >= b->f)
  {
     result = a;
     result->next = SortedMerge(a->next, b);
  }
  else
  {
     result = b;
     result->next = SortedMerge(a, b->next);
  }
  return(result);

}


void FrontBackSplit(builder_node* source,
          builder_node** frontRef, builder_node** backRef){

builder_node* fast;
 builder_node* slow;
if (source==NULL || source->next==NULL)
  {
    /* length < 2 cases */
    *frontRef = source;
    *backRef = NULL;
  }
else
  {
    slow = source;
    fast = source->next;
 
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }
 
    /* 'slow' is before the midpoint in the list, so split it in two
      at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }







}
















void builder_clean_list(builder_List list)
{
builder_node* ptr;
builder_node* cleaner; 
 
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


int builder_insert_to_end_sort(builder_List list,builder_node* nd)
{
        builder_node* komvos;
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






