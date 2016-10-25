#include<iostream>
using namespace std;

namespace Ex13
{
	struct IX	{		IX()	{	cout<<"X"<<endl;	}		};
	struct IY	{		IY()	{	cout<<"Y"<<endl;	}		};
	struct IZ	{		IZ()	{	cout<<"Z"<<endl;	}		};
	struct IA	{		IA()	{	cout<<"A"<<endl;	}		};
	struct IB	{		IB()	{	cout<<"B"<<endl;	}		};
	struct IC	{		IC()	{	cout<<"C"<<endl;	}		};

	struct SA : IX,IY,IZ
	{
		IA m_a;
		IB m_b;
		IC m_c;
		
		SA(){			cout<<"SA const"<<endl;		}
	};
};using namespace Ex13;
void main13()
{
	SA obj;
}
/*
x,y,z,a,b,c,sa
sa,x,y,z,a,b,c
x,y,z,sa,a,b,c
*/