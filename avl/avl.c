/***********************************************
 * Recursive Balanced Binary Search Tree (AVL) *
 * Developer: Tomer Alayof                     *
 * Written: 2021-01-26                         *
 *                                             *
 * Reviewer:   Daniella                        *
 **********************************************/

#include <stdlib.h> /*malloc()*/
#include <assert.h> /*assert()*/

#ifdef DEBUG
#include <stdio.h> /*printf()*/
#endif

#include "../include/avl.h"

enum children
{
    LEFT,
    RIGHT,
    NUM_CHILDREN
};

enum status
{
	SUCCESS = 0,
	FAILURE = 1
};

enum bool
{
	FALSE = 0,
	TRUE = 1
};

typedef struct avl_node avl_node_t;
typedef int (*order_func_t)(avl_t *avl, avl_action_func_t action_func, void *param);

static void DestroyNodes(avl_node_t *node);
static void * GetData(avl_node_t *node);
static void *GetNodeData(const avl_t *avl,avl_node_t *node, const void* data);

static avl_node_t *FindWhereToInsert(avl_t *avl,avl_node_t *where,void *data);
static avl_node_t *CreateNode(void *data);
static void UpdateHeight( avl_node_t * where);
static size_t Max(size_t a,size_t b);
static int CountActionFunc(void *data, void *param);

/*travers tree*/
static int PreOrder(avl_t *avl, avl_action_func_t action_func, void *param);
static int InOrder(avl_t *avl, avl_action_func_t action_func, void *param);
static int PostOrder(avl_t *avl, avl_action_func_t action_func, void *param);
static int TraverseInOrder(avl_node_t *node,avl_action_func_t action_func, void *param);
static int TraverseInPreOrder(avl_node_t *node,avl_action_func_t action_func, void *param);
static int TraverseInPostOrder(avl_node_t *node,avl_action_func_t action_func, void *param);
static order_func_t lut_order[NUM_OF_ORDERS] = {PreOrder,InOrder,PostOrder};

/*remove helpers*/
static avl_node_t *RecRemove(avl_node_t *node,const void *data, avl_cmp_func_t cmp_func);
static int HasTochilds(avl_node_t *node);
static avl_node_t *GetNext(avl_node_t *node);

/*balance*/
static int Balance(avl_node_t *node);
static size_t GetHeight(avl_node_t *node);
static avl_node_t *Rotate(avl_node_t *node, int direction);
static avl_node_t *DoubleSingleRotation(avl_node_t *node, int direction);
static avl_node_t * RefactorTree(avl_node_t * where);


#ifdef DEBUG
/*print functions*/
static void PrintNodeHeights(avl_node_t *root);
static void PrintTreeInOrderRec(avl_node_t *root);
static void PrintTreeCurrLevel(avl_node_t *root, int level);
#endif

struct avl_node
{
    void *data;
    size_t height; 
    avl_node_t *children[NUM_CHILDREN];
};

struct avl
{
    avl_node_t *root;
    avl_cmp_func_t cmp_func;
};

avl_t *AVLCreate(avl_cmp_func_t cmp_func)
{
	avl_t *avl = NULL;

	assert(NULL != cmp_func);

	avl = (avl_t *)malloc(sizeof(avl_t));
	if (NULL == avl)
	{
		return NULL;
	}

	avl->root = NULL;
	avl->cmp_func = cmp_func;

	return avl;
}

void AVLDestroy(avl_t *avl)
{
	assert(NULL != avl);

	DestroyNodes(avl->root);

	free(avl);
	avl = NULL;
}

int AVLInsert(avl_t *avl, void *data)
{
	assert(NULL != avl);
	assert(NULL != data);
	
	if(!AVLIsEmpty(avl))
	{	
	  avl->root = FindWhereToInsert(avl,avl->root,data);
	  if (NULL == avl->root)
	  {
	  	return FAILURE;
	  }
	}
	else
	{
		avl->root = CreateNode(data);
		if (NULL == avl->root)
		{
			return FAILURE;
		}
	}

	return SUCCESS;
}

void AVLRemove(avl_t *avl, const void *data)
{
	assert(NULL != avl);
	assert(NULL != data);

	avl->root = RecRemove(avl->root,data,avl->cmp_func);
}

void *AVLFind(const avl_t *avl, const void *data)
{
	assert(NULL != avl);
	assert(NULL != data);

	return GetNodeData(avl,avl->root,data);
}

int AVLIsEmpty(const avl_t *avl)
{
	assert(NULL != avl);

	return NULL == avl->root;
}

size_t AVLHeight(const avl_t *avl)
{
	assert(NULL != avl);

	return AVLIsEmpty(avl) ? 0 : avl->root->height;
}

size_t AVLSize(const avl_t *avl)
{
	int count = 0;

	assert(NULL != avl);

	AVLForEach((avl_t *)avl,&CountActionFunc,&count,IN_ORDER);

	return count;
}

int AVLForEach(avl_t *avl, avl_action_func_t action_func, void *param, order_t order)
{
	assert(NULL != action_func);
	assert(NULL != param);
	assert(NULL != avl);
	assert(order < NUM_OF_ORDERS);

	return lut_order[order](avl,action_func,param);
}

static avl_node_t *RecRemove(avl_node_t *node,const void *data, avl_cmp_func_t cmp_func)
{
	int compare = 0;

	if(NULL == node)
	{
		return node;
	}

	compare = cmp_func(GetData(node),data);
	if(compare == 0)
	{
		if (HasTochilds(node))
		{
			avl_node_t *temp = GetNext(node->children[RIGHT]);
			node->data = temp->data;
			data = temp->data;
		}
		else
		{
			avl_node_t *temp = node->children[node->children[LEFT] == NULL];
        	free(node);
        	node = NULL;
        	return temp;
		}
    }	

	node->children[compare <= 0] = RecRemove(node->children[compare <= 0], data ,cmp_func);

	node = RefactorTree(node);

	UpdateHeight(node);

	return node;
}

static avl_node_t *FindWhereToInsert(avl_t *avl,avl_node_t *where,void *data)
{
	int compare = avl->cmp_func(GetData(where),data);

	assert(0 != compare);

	if(NULL == where->children[compare < 0])
	{
		where->children[compare < 0] = CreateNode(data);
		if(NULL == where->children[compare < 0])
		{
			return NULL;
		}

		UpdateHeight(where);

		return where;
	}

	where->children[compare < 0] = FindWhereToInsert(avl,where->children[compare < 0],data);

	where = RefactorTree(where);

	UpdateHeight(where);

	return where;
}

static avl_node_t * RefactorTree(avl_node_t *where)
{
	int balance = Balance(where);

	if (balance == -2)
	{
		where = (Balance(where->children[LEFT]) == 1) ? DoubleSingleRotation(where,LEFT) : Rotate(where,LEFT);
	}

	else if (balance == 2)
	{
		where = (Balance(where->children[RIGHT]) == -1) ? DoubleSingleRotation(where,RIGHT) : Rotate(where,RIGHT);
	}

	return where;
}

static avl_node_t *DoubleSingleRotation(avl_node_t *node, int direction)
{
	avl_node_t *temp = node;
	avl_node_t *temp_child_direction = node->children[direction];

	node = temp->children[direction]->children[!direction];

	temp->children[direction]->children[!direction] = node->children[direction];
	node->children[direction] = temp->children[direction];
	temp->children[direction] = node->children[!direction];
	node->children[!direction] = temp;

	UpdateHeight(temp_child_direction);
	UpdateHeight(temp);

	return node;
}

static avl_node_t *Rotate(avl_node_t *node, int direction)
{
	avl_node_t *temp = node;

	node = temp->children[direction];
	temp->children[direction] = node->children[!direction];
	node->children[!direction] = temp;

	UpdateHeight(temp);

	return node;
}

static int Balance(avl_node_t *node)
{
	return GetHeight(node->children[RIGHT]) - GetHeight(node->children[LEFT]);
}

static size_t GetHeight(avl_node_t *node)
{
	return NULL == node ? 0 : node->height;
}

static avl_node_t *GetNext(avl_node_t *node)
{
	if(node->children[LEFT] == NULL)
	{
		return node;
	}

	return GetNext(node->children[LEFT]);
}

static int HasTochilds(avl_node_t *node)
{
	return (node->children[LEFT] != NULL && node->children[RIGHT] != NULL);
} 

static int InOrder(avl_t *avl, avl_action_func_t action_func, void *param)
{
	return TraverseInOrder(avl->root,action_func,param);
}

static int PreOrder(avl_t *avl, avl_action_func_t action_func, void *param)
{
	return TraverseInPreOrder(avl->root,action_func,param);	
}

static int PostOrder(avl_t *avl, avl_action_func_t action_func, void *param)
{
	return TraverseInPostOrder(avl->root,action_func,param);
}

static int TraverseInOrder(avl_node_t *node,avl_action_func_t action_func, void *param)
{
	int err_code = SUCCESS;

	if (NULL == node)
	{
		return err_code;
	}

	(void)(err_code != SUCCESS || (err_code += TraverseInOrder(node->children[LEFT],action_func,param)));
	(void)(err_code != SUCCESS || (err_code += action_func(GetData(node),param)));
	(void)(err_code != SUCCESS || (err_code += TraverseInOrder(node->children[RIGHT],action_func,param)));

	return err_code;
}

static int TraverseInPreOrder(avl_node_t *node,avl_action_func_t action_func, void *param)
{
	int err_code = SUCCESS;

	if (NULL == node)
	{
		return err_code;
	}

	(void)(err_code != SUCCESS || (err_code += action_func(GetData(node),param)));
	(void)(err_code != SUCCESS || (err_code += TraverseInPreOrder(node->children[LEFT],action_func,param)));
	(void)(err_code != SUCCESS || (err_code += TraverseInPreOrder(node->children[RIGHT],action_func,param)));

	return err_code;
}

static int TraverseInPostOrder(avl_node_t *node,avl_action_func_t action_func, void *param)
{
	int err_code = SUCCESS;

	if (NULL == node)
	{
		return err_code;
	}

	(void)(err_code != SUCCESS || (err_code += TraverseInPostOrder(node->children[LEFT],action_func,param)));
	(void)(err_code != SUCCESS || (err_code += TraverseInPostOrder(node->children[RIGHT],action_func,param)));
	(void)(err_code != SUCCESS || (err_code += action_func(GetData(node),param)));

	return err_code;
}

static avl_node_t *CreateNode(void *data)
{
	avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if(NULL == new_node)
	{
		return NULL;
	}

	new_node->data = data;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->height = 1;

	return new_node;
}

static void UpdateHeight(avl_node_t *where)
{
	size_t left = (NULL == where->children[LEFT]) ? 0 : where->children[LEFT]->height;
	size_t right = (NULL == where->children[RIGHT]) ? 0 : where->children[RIGHT]->height;

	where->height = 1 + Max(left,right);
}	

static size_t Max(size_t a,size_t b)
{
	return a > b ? a : b;
}

static void DestroyNodes(avl_node_t *node)
{
	if (NULL == node)
	{		
		return;
	}

	DestroyNodes(node->children[LEFT]);
	DestroyNodes(node->children[RIGHT]);

	free(node);
	node = NULL;
}

static void *GetNodeData(const avl_t *avl,avl_node_t *node, const void* data)
{
	int compare = 0;

	if (NULL == node)
	{	
		return NULL;
	}

	compare = avl->cmp_func(GetData(node),data);

	if (0 == compare)
	{
		return GetData(node);
	}

	return GetNodeData(avl,node->children[0 > compare],data);
}

static void *GetData(avl_node_t *node)
{
	assert(NULL != node);

	return node->data;
}

static int CountActionFunc(void *data, void *param)
{
	(void)data;
	++*(size_t *)param;
	return SUCCESS;
}

/*print funcs*/
#ifdef DEBUG
static void PrintTreeInOrderRec(avl_node_t *root)
{
	if (NULL != root)
	{
		PrintTreeInOrderRec(root->children[LEFT]);
		printf("%d, ", *(int *)GetData(root));
		PrintTreeInOrderRec(root->children[RIGHT]);
	}
}

static void PrintNodeHeights(avl_node_t *root)
{
	if (NULL != root)
	{
		PrintNodeHeights(root->children[LEFT]);
		printf("%lu, ", root->height);
		PrintNodeHeights(root->children[RIGHT]);
	}
}

static void PrintTreeCurrLevel(avl_node_t *root, int level)
{
	if (NULL == root)
	{
		return;
	}

	if (1 == level)
	{
		printf("%d, ", *(int *)GetData(root));
	}

	else if (1 < level)
	{
		PrintTreeCurrLevel(root->children[LEFT], level - 1);
		PrintTreeCurrLevel(root->children[RIGHT], level - 1);
	}
}

void PrintTreeByLevels(avl_t *tree)
{ /* this function will be deleted before production */
	size_t h = AVLHeight(tree);
	int i = 1;

	for (i = 1; i <= (int)h; ++i)
	{
		printf("level %d: ", i);
		PrintTreeCurrLevel(tree->root, i);
		printf("\n");
	}
}

void PrintTreeInOrder(avl_t *tree)
{ /* this function will be deleted before production */
	assert(NULL != tree);

	PrintTreeInOrderRec(tree->root);
	printf("\n");
	PrintNodeHeights(tree->root);
	printf("\n");
}
#endif