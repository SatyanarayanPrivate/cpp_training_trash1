namespace Ex22
{
	struct Date
	{
		Date(int dd,int mm,int yy)		{		}
	};
	struct Emp
	{
		Emp(int code)						{		}
	};
	struct Manager : Emp
	{
		Date doj;

		const int dept; 

		Manager():Emp(101),doj(1,1,1999),dept(123)		{		}
	};
};
using namespace Ex22;

void main22()
{
	Manager m1();
}