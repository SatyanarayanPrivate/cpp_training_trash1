
namespace Ex10
{
	struct Date
	{
		Date()
		{
		}
	};
	struct Emp
	{
		Date doj;
		/*
			Emp():doj.Date::Date()
			{
			}
		*/
	};
};
using namespace Ex10;

void main10()
{
	Emp e1;
}