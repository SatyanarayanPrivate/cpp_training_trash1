
namespace Ex27
{
	struct Date
	{
		~Date()		{		}
	};
	struct Emp
	{
		Date doj;
		/*
			~Emp()
			{
			}
			doj.Date::~Date()
		*/
	};
};
using namespace Ex27;

void main27()
{
	Emp e1;

}//e1.Emp::~Emp();