#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int get_second_from_time(const char *mtime)
{
	int n = 0, i;	
	int hs = 1, hsx = 1;
	int ret = 0;

	n = strlen(mtime);

	for (i = n-1; i >= 0 ; i--)
	{
		if( mtime[i] != ':')
		{
			ret += hs*(mtime[i] - '0') *hsx;	
			hsx *= 10;
		}
		else 
		{
			hsx = 1;
			hs *= 60;
		}
	}

	return ret;
}
int get_time_from_date(const char *date)
{
	char mtime[20];

	sscanf(date, "%*s%*s%*d%s%*d", mtime);

	return get_second_from_time(mtime);	
}
int main(void)
{
	char arr1[100] = "Sun Jul 21 0:06:12 2019";
	char arr2[100] = "Sun Jul 21 0:07:12 2019";

	printf("after get time1 : %d\n", get_time_from_date(arr1));
	printf("after get time2 : %d\n", get_time_from_date(arr2));

	return 0;
}
