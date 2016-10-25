#include<iostream>
using namespace std;

namespace Ex16
{
	struct SA
	{
		struct Static
		{
			int x;
			int y;
			int z;

			Static()
			{
				cout<<"static constructor"<<endl;
			}
		};
		
		static Static m_static;
	};
	SA::Static SA::m_static;
};
using namespace Ex16;

void main16()
{
	SA o1;
	SA o2;
	SA o3;
	SA o4;
}

















