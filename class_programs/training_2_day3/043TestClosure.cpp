#include<iostream>
using namespace std;


template<typename T>
void fun(T obj)
{
	cout << "fun called " << endl;
	obj();//callback
	cout << "fun ends " << endl;
	cout << "______________" << endl;
}



void DoJob()
{
	cout << "Hi from DoJob" << endl;
}

class CA//Function object
{
public:
	void operator()()
	{
		cout << "operator() for CA" << endl;
	}
};
void main()
{
	int i = 100;
	char * str = "sachin";
	CA ob;
	fun(&DoJob);
	
	fun(ob);
}