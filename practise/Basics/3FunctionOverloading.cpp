
namespace Ex5
{
	int			AddFun(int		 i,int		 j)	{		return i + j;		}
	double		AddFun(double i	  ,double j)	{		return i + j;		}
	float		AddFun(float	 i,float	 j)	{		return i + j;		}
};
using namespace Ex5;

void main5()
{
	AddFun(10,20);
	AddFun(123.45f,456.67f);
	AddFun(345435.546,567678.78);
}