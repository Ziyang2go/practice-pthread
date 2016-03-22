#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
pthread_rwlock_t rw_lock;
/**
 *This thread is responsble for pulling data off of the shared data
 *area
 */
 void *reader_thread(void* arg) {
	while(1) {
			if ( pthread_rwlock_rdlock(&rw_lock) != 0)
			{
				perror(" pthread_rd_lock");
				exit(1);
			}

			printf("reading......\n");


	if (pthread_rwlock_unlock(&rw_lock) != 0)
	{
		perror(" pthread_unlock");
		exit(1);
	}
	sleep(2);
	}
	return NULL;
}
/**
 *This thread is responsible for pulling data from a device
 */
 void *writer_thread(void * arg) {
 
		while(1) {
				if ( pthread_rwlock_wrlock(&rw_lock) != 0 )
				{
					perror("pthread_wrlock");
					exit(1);
				}
				printf("wrting....\n");

		
				if (pthread_rwlock_unlock(&rw_lock) != 0) 
				{
					perror("pthread_unlock");
					exit(1);
				}
				sleep(2);
			}
		return NULL;
}
#define M 10
#define N 20
int main(int argc, char* argv[])
{
	pthread_t R[N], W[M];
	pthread_rwlock_init(&rw_lock,NULL);
	for(int i = 0; i < N; ++i) {
			if( pthread_create(&R[i],NULL,reader_thread, NULL) != 0)
			{
				perror("pthread_create");
				exit(1);
			}
	}
	for(int i = 0; i < M; ++i) {
			if (pthread_create(&W[i],NULL, writer_thread, NULL) != 0)
			{
				perror("pthread_create");
				exit(1);
			}
	}
	for(int i = 0; i < N; ++i) {
			pthread_join(R[i],NULL);
	}
	for(int i = 0; i < M; ++i) {
			pthread_join(W[i],NULL);
	}
	return 0;
}
