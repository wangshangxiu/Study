#include<iostream>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
using namespace std;
#define N 10
void* T(void* v) {
	int t = *(int*)v;
	printf("pthread id = %d, value=%d\n", (int)pthread_self(), t);
	sleep(100);
}


int main(int argc, char* argv[]) {
	pthread_t t1[N];
	int args[N];
	int i =0;
	for (; i < N; i++) {
		args[i] = i;
		pthread_create(&t1[i], NULL, &T, &args[i]);
	}
	
	for (i =0 ; i < N; i++) {	
		pthread_join(t1[i], NULL);
	}
	
}
