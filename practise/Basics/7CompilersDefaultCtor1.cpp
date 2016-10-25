
namespace Ex9
{
	struct SA
	{
		SA()
		{
		}
	};
	struct SB :SA
	{
		/*
			SB():SA()
			{
			}
		*/
	};
};
using namespace Ex9;

void main9()
{
	SB obj;
	//obj.SB::SB();
}