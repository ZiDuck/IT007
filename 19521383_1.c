#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<semaphore.h>
int n;
int a[100000];
int dem = 0;
sem_t sem1;
void *pthread_a()
{
	while(1)
	{
		if (dem < n)
		{
			a[dem] = rand();
			dem++;
			printf("\n[PUSH]Size of array a: %d", dem);
		}
		sem_post(&sem1);
	}
}

void *pthread_b()
{
	int b;
	int j;
	while(1)
	{
		sem_wait(&sem1);
		if (dem == 0)
		{
			printf("\nNothing in array a");
		}
		else
		{
			b = rand() % dem;
			for(j = b; j < dem - 1; j++)
			{
				a[j] = a[j + 1];
			}
			dem--;
			if (dem == 0)
			{
				printf("\nNothing in array a");
			}
			else
			{
				printf("\n[POP]Size of array a: %d", dem);
			}
		}
	}
}
void main()
{
	sem_init(&sem1, 0, 0);
	printf("\nEnter n: ");
	scanf("%d", &n);
	pthread_t th1, th2;
	pthread_create(&th1, NULL, pthread_a, NULL);
	pthread_create(&th2, NULL, pthread_b, NULL);
	while(1);
}

