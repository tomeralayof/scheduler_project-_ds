#include <stdio.h> /* printf */
#include <unistd.h> /* sleep */

#include "../include/uid.h"

int main()
{
    int i = 0;
    for(i = 0; i < 50; ++i)
    {
        ilrd_uid_t myuid = UIDCreate();
        printf("my uid number %d is:\n u_id = %ld\n t_id = %ld\n p_id = %d\n",i, myuid.u_id, myuid.t_id, myuid.p_id);
        sleep(3);
    }
    return 0;
}
