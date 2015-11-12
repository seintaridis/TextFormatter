struct root{
	struct node* First;       //pointer to first node of list
	struct node* Last;        //pointer to last node of list
        int number;
        
		
               //number of nodes

};


struct node{

        struct node* next;
		struct node* previous;
        char*word;	
};


typedef struct node node;
typedef struct root* List;


List create_list(void);     //create root of a list
node* create_node(char*word);
int insert_to_end(List list,node* nd);
void print_all_from_first(List list);
int search_list(List list,char*word);
void clean_list(List list);
