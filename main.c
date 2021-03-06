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

typedef unsigned long t_bzero_elem;

void ft_bzero(void *s, size_t n)
{
	unsigned char	*sc;

	sc = (unsigned char *)s;
	while ((size_t)sc % sizeof(t_bzero_elem) && n)
	{
		*sc++ = 0;
		n--;
	}
	while (n >= sizeof(t_bzero_elem))
	{
		*(t_bzero_elem *)sc = 0;
		sc += sizeof(t_bzero_elem);
		n -= sizeof(t_bzero_elem);
	}
	while (n)
	{
		*sc++ = 0;
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

	size = 10000;
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
		before = GetTimeStamp();
		memset(buf,0, size);
		after = GetTimeStamp();
		printf("Memset time: %luus\n", after - before);
	}
	printf("Hello, World!\n");
	return 0;
}