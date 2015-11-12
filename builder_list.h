struct builder_root{
	struct builder_node* First;       //pointer to first node of list
	struct builder_node* Last;        //pointer to last node of list
    int number;
        
		
               //number of nodes

};


struct builder_node{

        struct builder_node* next;
		struct builder_node* previous;
        char*word;
		int f;	
};


typedef struct builder_node builder_node;
typedef struct builder_root* builder_List;


builder_List builder_create_list(void);     //create root of a list
builder_node* builder_create_node(char*word);
int builder_insert_to_end(builder_List list,builder_node* nd);
void builder_print_all_from_first(builder_List list,char*filename);
int builder_search_list(builder_List list,char*word);
void builder_clean_list(builder_List list);
void send_all(builder_List list,char* pipe_name);
builder_node* builder_create_node1(char*word,char* sixnotita);
void MergeSort(builder_node** list);
void builder_print_all_from_first1(builder_List list,char *filename,int k);
builder_node* SortedMerge(builder_node* a, builder_node* b);
void FrontBackSplit(builder_node* source,
          builder_node** frontRef, builder_node** backRef);
