#include<iostream>
using namespace std;

namespace Ex15
{
	struct SA
	{
		SA()							{	}//default constructor
		SA(int data)				{	}//overloaded constructor
		SA(int data,int datat2)	{	}//overloaded constructor2
		SA(SA& rhs)				{	}//copy const (clone, prototype)
		//???							  	  //static Constructor
		//???	   							  //Virtual Constructor
	};
};
using namespace Ex15;

void main15()
{
	SA o1; //default

	SA o2(123); //overloaded 

	SA o3 = 123; //overloaded

	SA o4(123,345); //overloaded 2

	SA o5(02);	//copy constructor

	SA o6 = o3; //copy constructor
}