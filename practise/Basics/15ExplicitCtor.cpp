namespace Ex18
{
	struct SA
	{
		//overloaded
		explicit SA(int data)	{		}
		
		//copy const (clone, prototype)
		explicit SA(SA& rhs)	{		}
	};
};
using namespace Ex18;

void main18()
{
	SA o2(123); //overloaded 

	//SA o3 = 123; //<-- error

	SA o5(o2);	//copy constructor

	//SA o6 = o2; //<-- error

}
