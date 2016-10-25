
namespace Ex11
{
	struct Emp
	{
		/*
			Emp()
			{
				initialize vptr for vitrual functions
			}
		*/

		virtual void fun() {}
	};
};
using namespace Ex11;

void main11()
{
	Emp e1;
}