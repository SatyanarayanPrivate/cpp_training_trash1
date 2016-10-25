#include<iostream>
using namespace std;

namespace Ex17
{
	struct Emp
	{
		Emp(int data)			{}
		virtual void dojob()	{}
	};
	struct Manager : Emp
	{
		virtual void dojob()	{ cout<<"manager dojob"<<endl;	}
	};
	struct Tester : Emp
	{
		virtual void dojob()	{ cout<<"tester dojob"<<endl;	}
	};
};
using namespace Ex17;

void main17()
{
	Emp* emp = new Emp(12);
	emp->dojob(); 
}