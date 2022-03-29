#include <stdlib.h> /*strtod*/
#include <assert.h> /*assert*/

#include "../include/parser.h"

char *GetNextOperator(const char *str, char *ch)
{
	assert(NULL != str);

	*ch = str[0];

	return (char *)str +1;
}

char *GetNextNum(const char *str, double *num)
{
	char *next = NULL;

	assert(NULL != str);

	*num = strtod(str,&next);

	return (str == next ? NULL : next);
}

