#include<iostream>
using namespace std;
#include"CallConstruction.h"

int main(int argc, char *argv[]) {
	CALLCONSTRUCTION a(1);
	CALLCONSTRUCTION * pa = &a;
	a.function1();	
	a.CALLCONSTRUCTION();
	cout << "hello" << endl;
}
