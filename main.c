#include "stdlib.h"
#include "string.h"

#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>

uint64_t GetTimeStamp()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec * (uint64_t) 1000000 + tv.tv_usec;
}

void ft_bzero(void *s, size_t n)
{
	unsigned char *arr;

	arr = (unsigned char *) s;
	while ((size_t) arr % sizeof(unsigned long) && n)
	{
		*arr++ = 0;
		n--;
	}
	while (n >= sizeof(unsigned long))
	{
		*(unsigned long *) arr++ = 0;
		n -= sizeof(unsigned long);
	}
	while (n)
	{
		*arr++ = 0;
		n--;
	}
}

void ft_bzero_old(void *s, size_t n)
{
	unsigned char *arr;
	size_t		   count;

	count = 0;
	arr	  = (unsigned char *) s;
	while (count < n)
		arr[count++] = 0;
}

int main()
{
	char *buf;

	buf = malloc(100 * 1000 * 1000);
	if (buf)
	{
		uint64_t before = GetTimeStamp();
		bzero(buf, 100 * 1000 * 1000);
		uint64_t after = GetTimeStamp();
		printf("Standard bzero time: %luus\n", after - before);
		before = GetTimeStamp();
		ft_bzero_old(buf, 100 * 1000 * 1000);
		after = GetTimeStamp();
		printf("My bzero_old time: %luus\n", after - before);
		before = GetTimeStamp();
		ft_bzero(buf, 100 * 1000 * 1000);
		after = GetTimeStamp();
		printf("My bzero time: %luus\n", after - before);
	}
	printf("Hello, World!\n");
	return 0;
}