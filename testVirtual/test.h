#ifndef TEST_VIRTUAL_H
#define TEST_VIRTUAL_H
#include<iostream>
using namespace std;
class TEST_VIRTUAL{
	public:
	virtual void test(void) = 0;
//	void test(void);
	virtual void show(void);
};

class SUB_TEST_VIRTUAL :public TEST_VIRTUAL {
	public:
		virtual void test(void);
		virtual void show(void);
};
#endif
