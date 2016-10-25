namespace Ex4
{
	extern "C++" void fun()
	{
	}
	extern "C++" void fun(int)
	{
	}
	extern "C" void fun2()
	{
	}
};
using namespace Ex4;

void main4()
{
	fun2();
	//call	_fun2

	fun();
	//call	?fun@@YAXXZ				
	fun(10);
	//call	?fun@@YAXH@Z			
}
