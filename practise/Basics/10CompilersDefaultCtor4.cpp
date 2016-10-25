
namespace Ex12
{
	struct Emp
	{
	};
	struct Manager : virtual Emp
	{
		/*
			Manager()
			{
				initialize vptr for vitrual functions
			}
		*/
	};
};
using namespace Ex12;

void main12()
{
	Emp e1;
}