#include<iostream>
using namespace std;

class A {
public: 
	A(){}
	~A(){}
private:
	int i;

	class B {
	public:
		B(A& a) {
			
			a.i = 1;
		}
		~B() {}
	};
	
};

int main (int argc, char* argv[]) {

	A *pa = new A();
}
