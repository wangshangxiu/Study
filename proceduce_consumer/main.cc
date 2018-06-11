#include<iostream>
//#include<thread>
//#include<mutex>
//#include<condition_variable>
#include<pthread.h>
//#include<mutex.h>
using namespace std;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
int cond = 1;

void *Tone(void* p) {

	pthread_mutex_lock(&mutex);
	cout << "excuting thread 1" << endl;
	if(cond ==1) {
		printf("A\n");
		cond++;
		pthread_cond_signal(&condition);
		pthread_cond_wait(&condition, &mutex);
	}

	pthread_mutex_unlock(&mutex);
}
void *Ttwo(void* p) {
	pthread_mutex_lock(&mutex);
	cout << "excuting thread 2" << endl;
	if(cond ==2) {
		printf("B\n");
		cond++;
		pthread_cond_signal(&condition);
		pthread_cond_wait(&condition, &mutex);
	}

	pthread_mutex_unlock(&mutex);
}
void *Tthree(void* p) {
	pthread_mutex_lock(&mutex);
	cout << "excuting thread 3" << endl;
	if(cond ==3) {
		printf("C\n");
		cond = 1;
		pthread_cond_signal(&condition);
		pthread_cond_wait(&condition, &mutex);
	}

	pthread_mutex_unlock(&mutex);
}

int main(int argc, char* argv[]) {
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;

	pthread_create(&t1, NULL, Tone, NULL);
	pthread_create(&t2, NULL, Ttwo, NULL);
	pthread_create(&t3, NULL, Tthree, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	return 0;
	
}
