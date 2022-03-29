#include <stdio.h> /*print*/
#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/

#define CASTING(type, var) (*(type *)&(var))

/*reviwed by dor*/

enum
{
	FALSE = 0,
	TRUE = 1
};

typedef struct Node
{
	void * data;
	struct Node *next;
}Node_t;

Node_t *CreateList();
void PrintList(Node_t *head);
Node_t *Flip(Node_t *head);
size_t size(Node_t *head);
Node_t * PromoteCurr(Node_t * curr,size_t result);
Node_t *FindIntersaction( Node_t * head1, Node_t * head2);
int HasLoop(Node_t *head);


int main()
{
	
	/*test eprahim -> passed*/
	
	Node_t *n1 = NULL, *n2 = NULL, *n3 = NULL, *n4 = NULL, *n5 = NULL;
	Node_t *m1 = NULL, *m2 = NULL, *m3 = NULL;
	
	n1 = (Node_t *)malloc(sizeof(Node_t));
	n2 = (Node_t *)malloc(sizeof(Node_t));
	n3 = (Node_t *)malloc(sizeof(Node_t));
	n4 = (Node_t *)malloc(sizeof(Node_t));
	n5 = (Node_t *)malloc(sizeof(Node_t));
	n5->next = n4;
	n4->next = n3;
	n3->next = n2;
	n2->next = n1;
	n1->next = NULL;

	assert(!HasLoop(n5));
	assert(n1 == Flip(n5));


	m1 = (Node_t *)malloc(sizeof(Node_t));
	m2 = (Node_t *)malloc(sizeof(Node_t));
	m3 = (Node_t *)malloc(sizeof(Node_t));
	m1->next = m2;
	m2->next = m3;
	m3->next = n4;
	assert(n4 == FindIntersaction(n1, m1));
	assert(n4 == FindIntersaction(n1, m1));

	
	m3->next = NULL;
	

	
	n5->next = n1;
	

	free(n1); n1 = NULL;
	free(n2); n2 = NULL;
	free(n3); n3 = NULL;
	free(n4); n4 = NULL;
	free(n5); n5 = NULL;
	free(m1); m1 = NULL;
	free(m2); m2 = NULL;
	free(m3); m3 = NULL;

	printf("SUCCESS\n");
	
		
	/*
	Node_t *head = NULL;
	Node_t *second = NULL;
	Node_t *third = NULL;
	Node_t *curr = NULL;
	Node_t *res = NULL;
	int has_loop = 0;
	 
	
	int x_1 = 1;
    int x_2 = 2;
    int x_3 = 3;
    
    void *data_1 = 	&x_1;
    void *data_2 = 	&x_2;
    void *data_3 = 	&x_3;
    
    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));
    
    head->data = data_1; 
    head->next = second; 
    
    second->data = data_2;
    second->next = third; 
    
    third -> data = data_3;
    third -> next = NULL;
    
    
    PrintList(head);
    printf("\n");
    
 
   	res = Flip(head);
    PrintList(res);
    

    has_loop = HasLoop(head);
    
    has_loop == TRUE ? printf("the list is circular\n") : printf("the list is linear \n");
    
    free(head);
    free(second);
    free(third); 
    */
    
	return 0;
}


Node_t *Flip(Node_t *head)
{

	Node_t *prev = head;
	Node_t *next = NULL;
	
	head = head -> next;
	prev -> next = NULL;
	next = head -> next;
	
	while(next != NULL)
	{
	
		head -> next = prev;
		prev = head;
		head = next;
		next = next -> next;
	}
	
	head -> next = prev;
	
	return head;
}

int HasLoop(Node_t *head)
{
	Node_t *turtle = head;
	Node_t *rabbit = head -> next;
	
	assert(NULL != head);
		
	while(NULL != rabbit && NULL != rabbit->next && turtle != rabbit )
	{	
		turtle = turtle -> next;
		rabbit = rabbit -> next -> next;
	}
	
	return turtle == rabbit;
}


void PrintList(Node_t *head)
{
	Node_t *curr = NULL;
	curr = head;
   	printf("my list:" );
   	
    while(curr -> next != NULL)
    {
    	printf(" %d ",*CASTING(int *, curr -> data));
    	
    	curr = curr -> next;
    	
    }
    
    printf("%d ",*CASTING(int *, curr -> data));
    printf("\n");
    
    curr = NULL;	
	
}

size_t size(Node_t *head)
{
    Node_t *current = head;
    int count = 0;
 
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    
    return count;
}


Node_t *FindIntersaction( Node_t * head1, Node_t * head2)
{
    Node_t *current1 = head1;
    Node_t *current2 = head2;
 	
 	size_t size_node_1 = size(head1);
 	size_t size_node_2 = size(head2);
 	
 	assert(NULL != head1);
 	assert(NULL != head1);
 	
 	if(size_node_1 > size_node_2)
 	{
 		current1 = PromoteCurr(current1,size_node_1 - size_node_2);
 	}
 	
 	else 
 	{
 		current2 = PromoteCurr(current2,size_node_2 - size_node_1);
 	}
 	
 	while(current1 != current2)
 	{	
 		current1 = current1 -> next;
 		current2 = current2 -> next;
 	} 
 	
 	return current1;
}


Node_t * PromoteCurr(Node_t * curr,size_t result)
{
	while(result > 0)
	{
		curr = curr -> next;
		--result; 
	}
	
	return curr;
}























