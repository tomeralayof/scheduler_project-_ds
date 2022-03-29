/*****************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          18/1/22                                                 ***
 *** Reviewer:      Gal 		                                            ***
 \*****************************************************************************
 *** Description:                                                           ***
 *** implementation for BST.	                                            ***
 ******************************************************************************
 \*****************************************************************************/

#include <stdlib.h> /*malloc()*/
#include <assert.h> /*assert()*/ 
#include <string.h> /*memset*/

#include "../include/bst.h"

#define I_AM(iter) ((iter) == ((iter)->parent->children[RIGHT]))
#define WHICH_CHILD(iter) (NULL != iter->children[RIGHT])

/*travel in the tree until node found*/
static bst_iter_t PromoteRunner(bst_iter_t tree_runner,bst_t *tree,void *data_to_find);

/*service function for creating new node*/
static bst_iter_t InitialNode(bst_iter_t new_node,bst_iter_t where,bst_t *tree,void *data);

/*go up in tree hirerachy by specific direction*/
static bst_iter_t IncreaseRunner(bst_iter_t runner,int index);

/*go down in tree hirerachy by specific direction*/
static bst_iter_t DecreaseRunner(bst_iter_t runner,int index1,int index2);

static bst_iter_t GetRoot(const bst_t * tree);

static int CountAction(void *data, void *count);

enum status
{
	SUCCESS = 0,
	FAILURE = 1
};

enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

typedef struct bst_node bst_node_t;

struct bst_node
{
    void *data;
    bst_node_t *parent;
    bst_node_t *children[NUM_OF_CHILDREN];
};

struct bst
{
    bst_node_t root_stub;
    bst_cmp_func_t CmpFunc;
};

bst_t *BSTCreate(bst_cmp_func_t cmp_func)
{
	bst_t * bst = NULL;

	bst = (bst_t *)malloc(sizeof(struct bst));
	if(NULL == bst)
	{
		return NULL;
	}
	
	bst->root_stub.data = NULL;
	bst->root_stub.parent = (bst_node_t *)&bst->root_stub;
	bst->root_stub.children[LEFT] = NULL;
	bst->root_stub.children[RIGHT] = NULL;
	
	bst->CmpFunc = cmp_func;
	
	return bst;
}

void BSTDestroy(bst_t *tree)
{
	bst_iter_t tree_runner = NULL;
	bst_iter_t next = NULL;
	
	assert(NULL != tree);
	
	tree_runner = BSTBegin(tree);
	
	while(!BSTIsEmpty(tree))
	{
		next = BSTNext(tree_runner);
		BSTRemove(tree_runner);
		tree_runner = next;
	}
	
	memset(tree, 0, sizeof(bst_t));
	free(tree);
	tree = NULL;
}

void *BSTGetData(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return iter->data;
}

int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);

	return iter1 == iter2;
}

int BSTIsEmpty(const bst_t *tree)
{
	assert(NULL != tree);
	
	return (GetRoot(tree) == NULL);
}

bst_iter_t BSTInsert(bst_t *tree, void *data)
{
	bst_iter_t new_node = NULL;
	bst_iter_t where = NULL;
	
	assert(NULL != tree);
	
	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if(NULL == new_node)
	{
		return (bst_node_t *)&tree->root_stub;
	}
	
	where = PromoteRunner(where,tree,data);
	
	new_node = InitialNode(new_node,where,tree,data);
	
	return new_node;
}

bst_iter_t BSTFind(const bst_t *tree, void *data_to_find)
{
	bst_iter_t tree_runner = NULL; 	
	
	assert(NULL != tree);
	
	tree_runner = PromoteRunner(tree_runner,(bst_t *)tree,data_to_find);
	
	return tree_runner;
}

bst_iter_t BSTEnd(const bst_t *tree)
{
	assert(NULL != tree);
	
	return tree->root_stub.parent;
}

bst_iter_t BSTNext(bst_iter_t iter)
{		
	assert(NULL != iter);
	
	return iter->children[RIGHT] == NULL ? IncreaseRunner(iter,RIGHT) : DecreaseRunner(iter,RIGHT,LEFT);
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
	assert(NULL != iter);
	
	return iter->children[LEFT] == NULL ? IncreaseRunner(iter,LEFT) : DecreaseRunner(iter,LEFT,RIGHT);
}

bst_iter_t BSTBegin(const bst_t *tree)
{	
	assert(NULL != tree);
	
	return DecreaseRunner(GetRoot(tree),LEFT,LEFT);
}

int BSTForEach(bst_iter_t from, bst_iter_t to, bst_action_func_t action_func, void *param)
{
	int status = SUCCESS;
	
	assert(NULL != from);	
	assert(NULL != to);
	
	while(from != to && status == SUCCESS)
	{
		status = action_func(BSTGetData(from),param);
		from = BSTNext(from);
	}
	
	return status;
}

size_t BSTSize(const bst_t *tree)
{
	size_t counter = 0;
	
	assert(NULL != tree);
	
	BSTForEach(BSTBegin(tree),BSTEnd(tree),&CountAction,&counter);
	
	return counter;
}

static int CountAction(void *data, void *count)
{
	(void)data;
	 
	++*(size_t *)count;
	
	return SUCCESS;
}

void BSTRemove(bst_iter_t iter)
{
   enum children link_child = 0;

    assert(NULL != iter);
    assert(NULL != BSTGetData(iter));

    if (NULL != iter->children[LEFT] && NULL != iter->children[RIGHT])
    {
        bst_iter_t next = BSTNext(iter);
        iter->data = next->data;
        iter = next;
    }

    link_child = (WHICH_CHILD(iter));
    iter->parent->children[I_AM(iter)] = iter->children[link_child];

    if (NULL != iter->children[link_child])
    {
        iter->children[link_child]->parent = iter->parent;
    }

    memset(iter, 0, sizeof(bst_node_t));
    free(iter); 
    iter = NULL;
}

static bst_iter_t DecreaseRunner(bst_iter_t runner,int index1,int index2)
{
	if(runner->children[index1] != NULL)
	{
		runner = runner->children[index1];
	}
		
	while(runner->children[index2] != NULL)
	{	
		runner = runner->children[index2];
	}
	
	return runner;
}

static bst_iter_t IncreaseRunner(bst_iter_t runner,int index)
{
	bst_iter_t prev = runner;
		
	do
	{
		prev = runner;
		runner = runner->parent;
	} while(prev == runner->children[index]);

	return runner;
}

static bst_iter_t InitialNode(bst_iter_t new_node,bst_iter_t where,bst_t *tree,void *data)
{
	if(!BSTIsEmpty(tree))
	{
		int compare = tree->CmpFunc(BSTGetData(where),data);
		
		assert(0 != compare);
		
		new_node->parent = where;
		where->children[compare < 0] = new_node;
	}
	else
	{
		tree->root_stub.children[LEFT] = new_node;
		new_node->parent = (bst_node_t *)&tree->root_stub;
	}
	
	new_node->data = data;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	
	return new_node;
}

static bst_iter_t PromoteRunner(bst_iter_t tree_runner,bst_t *tree,void *data_to_find)
{	
	int status = 1;

	assert(NULL != tree);
	
	tree_runner = GetRoot(tree);
	
	while (NULL != tree_runner && (status = tree->CmpFunc(BSTGetData(tree_runner),data_to_find)) != 0)
	{		
		if(NULL != tree_runner->children[RIGHT] && status < 0)
		{
			tree_runner = tree_runner->children[RIGHT];	
		}	
		else if (NULL != tree_runner->children[LEFT] && status > 0)
		{
			tree_runner = tree_runner->children[LEFT];
		}		
		else
		{
			break;
		}
	}
	
	return tree_runner;
}

static bst_iter_t GetRoot(const bst_t * tree)
{
	assert(NULL != tree);

	return tree->root_stub.children[LEFT];
}