#include <stdio.h>
#include <stdlib.h>

#include "../include/parser.h"

int main()
{


	const char *str = "12345+12345";
	char ch = 0;
	double num = 0;

	GetNextNum(&str,&num);

	printf("%s\n",str);
	printf("%f\n",num);

	return 0;


	/*
	const char *str = "+12345";
	const char *str2 = "12345+500";
	double num = 0;
	char ch = 0;
	char *returned_ch = NULL;


	char *str3;

	returned_ch = GetNextOperator(str,&ch);

	printf("%c\n", ch);
	printf("%s\n",returned_ch);

	str3 = GetNextNum(str2,&num);

	printf("%f\n", num);
	printf("str3: %s\n", str3);

	return 0;
	*/
}
