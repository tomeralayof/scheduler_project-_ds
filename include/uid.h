#ifndef __ILRD_UID_H__
#define __ILRD_UID_H__

#include <sys/types.h> /* size_t, time_t, pid_t */

typedef struct
{
	size_t u_id;
	time_t t_id;
	pid_t p_id;
} ilrd_uid_t;

extern const ilrd_uid_t UIDBadUID;

/* Complexity: O(1) time, O(1) space. */
ilrd_uid_t UIDCreate(void);

/* Complexity: O(1) time, O(1) space. */
int UIDIsSame(const ilrd_uid_t uid1, const ilrd_uid_t uid2);

#endif /* __ILRD_UID_H__ */
