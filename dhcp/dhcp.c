/*****************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          12/2/22                                                 ***
 *** Reviewer:      Nurit 		                                            ***
 \*****************************************************************************
 *** Description:                                                           ***
 *** implementation for dhcp.	                                            ***
 ******************************************************************************
 \*****************************************************************************/
 
#include <assert.h> /*assert()*/
#include <stdlib.h> /*malloc()*/
#include <string.h> /*strcmp()*/

#include "../include/dhcp.h"

#define SWAP_INT32(x) (((x) >> 24) | (((x) & 0x00FF0000) >> 8) | (((x) & 0x0000FF00) << 8) | ((x) << 24))
#define IP_BITS (32)

typedef struct trie_node trie_node_t;

static dhcp_t *InitDhcp(dhcp_t *dhcp,const char *network_address, unsigned int subnet_mask_size);
static int StrToInt(const char *str);
static char *IntToStr(int num,char *arr);
static unsigned int GetNum(unsigned int levels,const char *requested_ip_address);
static unsigned int PromoteMask(unsigned int levels);
static trie_node_t *InitNode();
static int InitialAddresses(dhcp_t *dhcp);
static void RecursiveFreeNodes(trie_node_t * root);
static char *UpdateAddress(dhcp_t *dhcp,char *result_ip_address,unsigned int Final_ip_result,unsigned int levels);
static unsigned int FixRepresentation(unsigned int levels, unsigned int Binary_representation,unsigned int Final_ip_result);
static trie_node_t* tryCreateIP(unsigned int num,trie_node_t* root, unsigned int mask, unsigned int level,unsigned int *final_ip);
static int ChildExist(unsigned int num,unsigned int mask,trie_node_t*root);
static int IsExist(trie_node_t *root,unsigned int level,unsigned int num,unsigned int mask);
static size_t RecCount(trie_node_t *root,unsigned int level);
static void RecFree(trie_node_t *root, unsigned int level,unsigned int mask , unsigned int num);
static int IsFree(trie_node_t *root, unsigned int num, unsigned int mask, unsigned int level);

enum
{
    LEFT = 0,
    RIGHT = 1,
    NUM_OF_CHILDREN
};

enum bool
{
    FALSE,
    TRUE
};

struct trie_node
{
	char is_allocated;
    trie_node_t *children[NUM_OF_CHILDREN];
};

struct dhcp
{
	unsigned int subnet_mask_size;
	const char *base_address;
    trie_node_t *root;
};


dhcp_t *DHCPCreate(const char *network_address, unsigned int subnet_mask_size)
{
    dhcp_t *dhcp = NULL;

    assert(NULL != network_address);
    assert(0 < subnet_mask_size && subnet_mask_size <= 29);

    dhcp = InitDhcp(dhcp,network_address,subnet_mask_size);
    if (NULL ==  dhcp)
    {
        return NULL;
    }

    dhcp->root = InitNode();
    if (NULL == dhcp->root)
    {
        free(dhcp);
        dhcp = NULL;

        return NULL;
    }

    if(FAILURE == InitialAddresses(dhcp))
    {
        DHCPDestroy(dhcp);

        return NULL;
    }

    return dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
    assert(NULL != dhcp);

    RecursiveFreeNodes(dhcp->root);
    dhcp->root = NULL;

    free(dhcp);
    dhcp = NULL;
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
    unsigned int level = 0;
    unsigned int total_options = 0;
     
    assert(NULL != dhcp);

    level =  IP_BITS - dhcp->subnet_mask_size;
    total_options = 1 << level;

    return total_options - RecCount(dhcp->root,level);
}

status_t DHCPFreeIP(dhcp_t *dhcp, const char *ip_address_to_free)
{
    unsigned int levels = 0;
    unsigned int mask = 0;
    unsigned int num = 0;

    assert(NULL != dhcp);
    assert(strcmp(ip_address_to_free,"255.255.255.254") != 0);
    assert(strcmp(ip_address_to_free,"255.255.255.255") != 0);
    assert(strcmp(ip_address_to_free,"000.000.000.000") != 0);

    levels = IP_BITS - dhcp->subnet_mask_size;
    mask =  PromoteMask(levels);
    num = GetNum(levels,ip_address_to_free);
        
    if (!IsExist(dhcp->root,levels,num,mask) || IsFree(dhcp->root,num,mask,levels))
    {
       return DOUBLE_FREE;
    }

    RecFree(dhcp->root,levels + 1,mask,num);

    return SUCCESS;
}

static int IsFree(trie_node_t *root, unsigned int num, unsigned int mask, unsigned int level)
{
    unsigned int i = 0;
    size_t count = 0;

    for (i = 0; i < level + 1; i++)
    {
        if (!root->is_allocated)
        {
            ++count;
        }
        root = root->children[(num & mask) > 0];
        mask = mask >> 1;
    }

    return count == level+1;
}

status_t DHCPAllocateIP(dhcp_t *dhcp, const char *requested_ip_address, char *result_ip_address)
{
    unsigned int levels = 0;
    unsigned int num = 0;
    unsigned int mask = 0;
    trie_node_t *root = NULL;
    unsigned int Final_ip_result = 0;
    char *next_free = "000.000.000.000";
    int is_exist = FALSE;

    assert(NULL != dhcp);
    assert(NULL != result_ip_address);

    levels = IP_BITS - dhcp->subnet_mask_size;
    mask = PromoteMask(levels);
    root = dhcp->root;

    if (requested_ip_address != NULL)
    {
        num = GetNum(levels,requested_ip_address);
    }

    is_exist = IsExist(root,levels,num,mask);
    num = is_exist ? GetNum(levels,next_free) : num;

    if (NULL == tryCreateIP(num,root,mask,levels + 1,&Final_ip_result))
    {
        return FAILURE;
    }
 
    result_ip_address = UpdateAddress(dhcp,result_ip_address,Final_ip_result,levels);
     
    return SUCCESS;
}

static void RecFree(trie_node_t *root, unsigned int level,unsigned int mask , unsigned int num)
{
    unsigned int direction = (mask & num) > 0;
    if (NULL == root)
    {
        return;
    }

    root->is_allocated = FALSE;

    RecFree(root->children[direction],level - 1,mask >> 1,num);
}

static size_t RecCount(trie_node_t *root,unsigned  int level)
{
    if (root == NULL)
    {
        return 0;
    }
    if (level == 0)
    {
       return root->is_allocated;
    }
    else if (root->is_allocated == TRUE)
    {
       return 1 << (level - 1);
    }
    
    return RecCount(root->children[LEFT],level-1) + RecCount(root->children[RIGHT],level-1);
}

static int InitialAddresses(dhcp_t *dhcp)
{  
    char *lsb_ip = "000.000.000.000";
    char *msb_ip = "255.255.255.255";
    char *msb_ip_2 = "255.255.255.254";
    char filler[20] = {0};

    if (FAILURE ==  DHCPAllocateIP(dhcp,lsb_ip,filler))
    {
        return FAILURE;
    }
    
    if (FAILURE == DHCPAllocateIP(dhcp,msb_ip,filler))
    {
        return FAILURE;
    }
    
    if (FAILURE == DHCPAllocateIP(dhcp,msb_ip_2,filler))
    {
        return FAILURE;
    }
      
    return SUCCESS;
}

static trie_node_t *InitNode()
{
    trie_node_t *new_node = (trie_node_t *)malloc(sizeof(trie_node_t));
    if (new_node == NULL)
    {
        return NULL;
    }

    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;
    new_node->is_allocated = FALSE;

    return new_node;
}

static dhcp_t *InitDhcp(dhcp_t *dhcp,const char *network_address, unsigned int subnet_mask_size)
{
    dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
    if (dhcp == NULL)
    {
        return NULL;
    }

    dhcp->subnet_mask_size = subnet_mask_size;
    dhcp->base_address = network_address;

    return dhcp;
}

static trie_node_t *tryCreateIP(unsigned int num,trie_node_t *root, unsigned int mask,
                                     unsigned int level,unsigned int *final_ip)
{
   unsigned int currentBit = ((num & mask) > 0);

    if (NULL == root)
    {
       return root;
    }
    if(1 == level)
    {
        root->is_allocated = TRUE;
        return root;
    }
    if(root->children[currentBit] == NULL)
    {
        root->children[currentBit] = InitNode();
        if (root->children[currentBit] == NULL)
        {
            return NULL;
        }
    }
    else if(root->children[currentBit]->is_allocated)
    {   
        currentBit = !currentBit;
    }

    if(currentBit > 0)
    {
        *final_ip|= mask;
    }
    
    tryCreateIP(num, root->children[currentBit],mask >> 1, level - 1,final_ip);

    return root;
}

static int IsExist(trie_node_t *root,unsigned int level,unsigned int num,unsigned int mask)
{
    unsigned int i = 0;
    size_t count = 0;

    for (i = 0; i < level + 1 && ChildExist(num,mask,root); i++)
    {
        ++count;
        root = root->children[(num & mask) > 0];
        mask >>= 1;
    }

    return (count == level);
}

static int ChildExist(unsigned int num,unsigned int mask,trie_node_t*root)
{
    return root->children[(num & mask) > 0] != NULL;
}

static char *UpdateAddress(dhcp_t *dhcp,char *result_ip_address,unsigned int Final_ip_result,unsigned int levels)
{  
    unsigned int Binary_representation = StrToInt(dhcp->base_address);
    Binary_representation = SWAP_INT32(Binary_representation);
    Binary_representation = FixRepresentation(levels,Binary_representation,Final_ip_result);/*representation*/
    IntToStr(SWAP_INT32(Binary_representation),result_ip_address);
    return result_ip_address;
}

static unsigned int FixRepresentation(unsigned int levels, unsigned int Binary_representation,unsigned int Final_ip_result)
{
    unsigned int i = 0;
    unsigned int mask = 1;

    for (i = 0; i < levels; i++)
    {
        Binary_representation|=mask;
        Binary_representation^=mask;
        mask <<= 1;
    }

    return Binary_representation|=Final_ip_result;
}

static unsigned int PromoteMask(unsigned int levels)
{
    unsigned int mask = 1;

    while (levels > 1)
    {
        mask <<= 1;
        --levels;
    }
    return mask;
}

static unsigned int GetNum(unsigned int levels,const char *requested_ip_address)
{
    unsigned int mask = 0;

    unsigned int num_to_check = StrToInt(requested_ip_address);
    num_to_check = SWAP_INT32(num_to_check);

    while (levels > 0)
    {
       mask <<= 1;
       mask+=1;
       --levels;
    }
    
    return (mask & num_to_check);
}

static void RecursiveFreeNodes(trie_node_t *root)
{
    if (root == NULL)
    {
        return;
    }

    RecursiveFreeNodes(root->children[LEFT]);
    RecursiveFreeNodes(root->children[RIGHT]);

    free(root);
    root = NULL;
}

static int StrToInt(const char *str)
{ 
    unsigned int x = 0;
    inet_pton(AF_INET,str,&x);
    return x;
}

static char *IntToStr(int num, char *arr)
{  
    uint32_t ip = num;
    inet_ntop(AF_INET,&ip,arr,16);
    return arr;
}