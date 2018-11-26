
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

// size of array

int MAX=0;

//#define MAX_THREAD 4


int *data;//= { 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220 };
int sum[4] = { 0 };
int part = 0;
int threadsNumber =  NUM_THREADS;

 void InitializeArray(int arr_size){
 	printf("input array elements: ");
 	int i;

 	data = (int *)malloc(arr_size*sizeof(int));

 	for(i=0; i<arr_size; i++)
 		scanf("%d", &data[i]);

 }



void *ArraySum(void *d)
{

	// Each thread computes sum of 1/4th of array
	int thread_part = part++;
    int i;
    int flag=0;

    if(MAX%2==0)
        flag = 0;
    else
        flag = 1;

    for (i = (thread_part * (MAX / NUM_THREADS-flag)); i < (thread_part+1) * (MAX / NUM_THREADS); i++)
		sum[thread_part] += data[i];

    threadsNumber--;
}

// Driver Code
int main()
{

	pthread_t threads[NUM_THREADS];
	printf("input array size: ");
 	scanf("%d", &MAX);

	InitializeArray(MAX);

	// Creating 4 threads
	int i;
	for (i = 0; i < NUM_THREADS; i++)
		pthread_create(&threads[i], NULL, ArraySum, (void*)NULL);


	// joining 4 threads i.e. waiting for all 4 threads to complete
	for (i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

    while (threadsNumber!=0);
    int total_sum = 0;
	for (i = 0; i < NUM_THREADS; i++)
		total_sum += sum[i];

    printf("The sum of the array elements is: %d",total_sum);

	return 0;
}
