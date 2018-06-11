#include<iostream>
using namespace std;

typedef struct {
	int type;
	long long integer;
} NULLTEST;

int main(int argc, char *argv[]) {
	NULLTEST * nt = nullptr;
	if (nt->type == 0) {
		cout << nt->type <<endl;
	} else {
		cout <<	nt->integer <<endl;
	}	
}
