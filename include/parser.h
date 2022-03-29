/**********************************\
* str_parse                        *
* Developer: Tomer Alayof          *
* Written: 2021-1-20               *
*                                  *
* Reviewer:                        *
\**********************************/

#ifndef __STR_PARSE_H__
#define __STR_PARSE_H__

#include <stddef.h> /*null*/

/*char *GetNextNum(const char *str, double *num);*/

char *GetNextNum(const char *str, double *num);


/* get first number in str using strod(). putting result in num
   return success or failure. */

char *GetNextOperator(const char *str, char *ch);
/* manual, searching for first appearance of +,-,*,/,^,(,) in str
   putting result in ch. return success or failure  */

#endif /* __STR_PARSE_H__ */
