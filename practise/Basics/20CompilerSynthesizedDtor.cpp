
namespace Ex26
{
	struct SA
	{
		~SA()		{		}
	};
	struct SB :SA
	{
		/*
			~SB()
			{
			} this->SA::~SA()
		*/
	};
};
using namespace Ex26;

void main26()
{
	SB obj;

}	//obj.SB::~	SB();
