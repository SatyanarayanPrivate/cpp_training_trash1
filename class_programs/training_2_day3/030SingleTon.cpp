#include<iostream>
using namespace std;
namespace nm30
{
	class CA
	{
		CA()
		{
			cout << "CA Ctor" << endl;
		}
		~CA()
		{
			cout << "CA D-tor" << endl;
		}
		static CA *head;
		static CA* CreateCA()
		{
			if (head == NULL)
				head = new CA();
			return head;
		}
		static void Release()
		{
			delete head;
			head = NULL;
		}
	public:
		void fun()
		{
			cout << "CA fun called " << endl;
		}
		friend class Smart;
	};
	CA* CA::head = NULL;

	class Smart
	{
		CA *ptr;
		static int count;
	public:
		Smart() :ptr(CA::CreateCA())
		{
			count++;
		}
		CA* operator->()
		{
			return ptr;
		}
		~Smart()
		{
			count--;
			if (count == 0)
				CA::Release();
		}
	};
	int Smart::count = 0;
	void main()
	{

		Smart smt1;
		Smart smt2;
		Smart smt3;
		Smart smt4;
		smt1->fun();

	}
}