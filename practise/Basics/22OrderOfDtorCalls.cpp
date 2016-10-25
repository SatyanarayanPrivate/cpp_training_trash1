#include<iostream>
using namespace std;

namespace Ex28
{
	struct IX{	~IX()	{	cout<<"IX dest"<<endl;	}	};
	struct IY{	~IY()	{	cout<<"IY dest"<<endl;	}	};
	struct IZ{	~IZ()	{	cout<<"IZ dest"<<endl;	}	};
	struct IA{	~IA()	{	cout<<"IA dest"<<endl;	}	};
	struct IB{	~IB()	{	cout<<"IB dest"<<endl;	}	};
	struct IC{	~IC()	{	cout<<"IC dest"<<endl;	}	};

	class SA : public IX,public IY,public IZ
	{
		IA m_a;
		IB m_b;
		IC m_c;
	public:	
		~SA()	{	cout<<"SA dest"<<endl; }
	};
};
using namespace Ex28;

void main28()
{
	SA obj;
}

/*
ix,iy,iz,ia,ib,ic,sa

sa,ic,ib,ia,iz,iy,ix


*/











