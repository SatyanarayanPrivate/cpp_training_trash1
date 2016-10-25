namespace Ex3
{
	void fun()  {}

	void fun(int i) {}

	namespace n1
	{
		void fun() {}
	}

	class CA
	{
	public:
		static void fun()	{	}
	};
};
using namespace Ex3;

void main3()
{
	fun();
	//call	?fun@@YAXXZ				

	fun(10);
	//call	?fun@@YAXH@Z

	n1::fun();
	//call	?fun@n1@@YAXXZ				

	CA::fun();
	//call	?fun@CA@@SAXXZ	
}