/*****************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          12/2/22                                                 ***
 *** Reviewer:      Nurit 		                                            ***
 \*****************************************************************************
 *** Description:                                                           ***
 *** header file for dhcp.  	                                            ***
 ******************************************************************************
 \*****************************************************************************/


#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /* size_t */
#include <arpa/inet.h>


typedef struct dhcp dhcp_t;

typedef enum status
{
	SUCCESS = 0,
	DOUBLE_FREE = 1,
	FAILURE = 2
}status_t;

/* time complexity O(1?) */
/* max of subnet mask size must be 29 */
dhcp_t *DHCPCreate(const char *network_address, unsigned int subnet_mask_size);

/* time complexity eager : O(1?) */
void DHCPDestroy(dhcp_t *dhcp);

/*time complexity O(logn)*/
status_t DHCPAllocateIP(dhcp_t *dhcp, const char *requested_ip_address, char *result_ip_address);
/*
1. give the user the smallest ip possible, if he dont request nothing specific. user send NULL if this is the case.
2. give the user the smallest ip possible according to his request.
*/

/*time complexity O(logn)*/
/* if the requested ip adress is not allocated, a double free error must be returned */
/* if the requested ip adress is not in our range, ignore this case */
status_t DHCPFreeIP(dhcp_t *dhcp, const char *ip_address_to_free);

/*time complexity O(n)*/
size_t DHCPCountFree(const dhcp_t *dhcp);

#endif /*__DHCP_H__ */