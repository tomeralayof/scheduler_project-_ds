#include <pthread.h>
#include <unistd.h> /* getpid() */
#include <time.h>   /* time() */

#include "../include/uid.h"

const ilrd_uid_t UIDBadUID = { 0, 0, 0 };

ilrd_uid_t UIDCreate(void)
{
	
	static size_t uidc = 0;
	
	ilrd_uid_t uid = {0};

	uid.u_id = __sync_add_and_fetch(&uidc,1);
	
	uid.t_id = time(NULL);
	
	uid.p_id = getpid();
	
    if ((time_t)(-1) == uid.t_id)
    {
    	uid = UIDBadUID;
    }
	
	return uid;	
}

int UIDIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2)
{
	return (uid1.u_id == uid2.u_id && uid1.t_id == uid2.t_id && uid1.p_id == uid2.p_id);
}
