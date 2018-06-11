#include<iostream>
#include<string>
using namespace std;
int main(int argc, char *argv[]) {
	string tmp("hello");
	cout << tmp <<endl;
	tmp.append(" world");
	cout << tmp.size() <<endl;	
	cout << tmp <<endl;
//	tmp[tmp.size()] ='!';
	tmp.insert(tmp.size(),1, '!');
	cout << tmp << endl;
	
	cout << tmp.size() <<endl;
	
	cout << tmp[tmp.size()] <<endl;
	tmp.replace(tmp.size()-1, 1, ".");
	cout << tmp.size() << endl;
	cout << tmp << endl;
//	tmp.at(tmp.size());
}
