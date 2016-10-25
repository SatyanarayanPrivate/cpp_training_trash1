#include<iostream>
using namespace std;
			
namespace Ex23
{
	struct SA
	{
		int x;
		int y;
		int z;

		SA(int data):z(data),y(z + 10),x(y+10)
		{
		}
	};
};
using namespace Ex23;

void main23()
{
	SA obj(100);

	cout<<obj.x<<endl;
	cout<<obj.y<<endl;
	cout<<obj.z<<endl;
}
