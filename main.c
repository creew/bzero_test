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
	while ((size_t)s % sizeof(unsigned long) && n)
	{
		*(unsigned char *)s++ = 0;
		n--;
	}
	while (n >= sizeof(unsigned long))
	{
		*(unsigned long *)s++ = 0;
		n -= sizeof(unsigned long);
	}
	while (n)
	{
		*(unsigned char *)s++ = 0;
		n--;
	}
}

void ft_bzero_old(void *s, size_t n)
{
	unsigned char	*arr;
	size_t			count;

	count = 0;
	arr	  = (unsigned char *) s;
	while (count < n)
		arr[count++] = 0;
}

int main()
{
	char		*buf;
	size_t		size;

	size = 1000 * 1000 * 1000;
	buf = malloc(size);
	if (buf)
	{
		uint64_t before = GetTimeStamp();
		bzero(buf, size);
		uint64_t after = GetTimeStamp();
		printf("Standard bzero time: %luus\n", after - before);
		before = GetTimeStamp();
		ft_bzero_old(buf, size);
		after = GetTimeStamp();
		printf("My bzero_old time: %luus\n", after - before);
		before = GetTimeStamp();
		ft_bzero(buf, size);
		after = GetTimeStamp();
		printf("My bzero time: %luus\n", after - before);
	}
	printf("Hello, World!\n");
	return 0;
}