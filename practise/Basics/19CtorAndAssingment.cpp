#include<iostream>
using namespace std;

namespace Ex24
{
	struct Date
	{
		Date()							{	cout<<"def const"<<endl;				}
		Date(char* dt)					{	cout<<"overloaded const"<<endl;		}
		void operator=(char* dt)	{	cout<<"= operator "<<endl;				}
	};
	struct SA
	{
		Date doj;

		SA():doj("1/1/1999")  
		{
			//doj = "1/1/1999";   
		}
	};
};
using namespace Ex24;

void main24()
{
	SA obj;
}