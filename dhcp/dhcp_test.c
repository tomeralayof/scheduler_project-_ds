/*****************************************************************************
 *** Written by:    Tomer Alayof                                            ***
 *** Date:          12/2/22                                                 ***
 *** Reviewer:      Nurit 		                                            ***
 \*****************************************************************************
 *** Description:                                                           ***
 *** tests for dhcp.	                                            ***
 ******************************************************************************
 \*****************************************************************************/

#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include "../include/dhcp.h"

void TestCreate();
void TestAllocate();

int main()
{
    /*
    TestCreate();
    */
   TestAllocate();
    return 0;
}

void TestCreate()
{
    const char *network_address = "192.168.10.15";
    unsigned int subnet_mask_size = 28;

    dhcp_t *dhcp = DHCPCreate(network_address,subnet_mask_size);

    DHCPDestroy(dhcp);
}

void TestAllocate()
{
    const char *network_address = "192.168.10.15";
    unsigned int subnet_mask_size = 28;

    char *result1 = malloc(20);
    char *result2 = malloc(20);
    char *result3 = malloc(20);

    dhcp_t *dhcp = DHCPCreate(network_address,subnet_mask_size);

    DHCPAllocateIP(dhcp,"255.255.255.253",result1);
    DHCPAllocateIP(dhcp,"255.255.255.252",result2);
    DHCPAllocateIP(dhcp,"255.255.255.255",result3);

    DHCPFreeIP(dhcp,"255.255.255.253");
    DHCPFreeIP(dhcp,"255.255.255.253");

    /*
    printf("%s\n",result1);
    printf("%s\n",result2);
    printf("%s\n",result3);
    */


    printf("count: %ld\n",DHCPCountFree(dhcp));

    /*DHCPFreeIP(dhcp,"255.255.255.250");*/

    
    printf("count: %ld\n",DHCPCountFree(dhcp));
    printf("-----------\n");
    DHCPFreeIP(dhcp,"255.255.255.199");
    DHCPFreeIP(dhcp,"255.255.255.252");
    DHCPFreeIP(dhcp,"255.255.255.253");
     

    free(result2);
    free(result1);
    free(result3);

    DHCPDestroy(dhcp);
}