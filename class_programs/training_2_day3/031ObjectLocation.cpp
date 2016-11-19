#include<iostream>
using namespace std;
namespace nm31
{
	class CA
	{
		bool IsOnHeap;
		static bool GlobalHeap;
		static int GlobalCount;
	public:
		CA() :IsOnHeap(GlobalHeap)
		{
			GlobalCount--;
			if (GlobalCount <= 0)
				GlobalHeap = false;
		}
		static void * operator new(size_t size)
		{
			void *pt = malloc(size);
			GlobalHeap = true;
			//((CA*)pt)->IsOnHeap = true;
			return pt;
		}
			static void * operator new[](size_t size)
		{
			void *pt = malloc(size);
			GlobalHeap = true;
			GlobalCount = size / sizeof(CA);
			//((CA*)pt)->IsOnHeap = true;
			return pt;
		}
			void ObjectLocation()
		{
			if (IsOnHeap == true)
			{
				cout << "Object is on heap " << endl;
			}
			else
			{
				cout << "Object is (not) on heap " << endl;
			}
		}
	};
	bool CA::GlobalHeap = false;
	int CA::GlobalCount = 0;

	void main()
	{
		CA obj1;
		CA *ptr1 = new CA();
		CA *ptr2 = new CA();
		/*
		push	1
		call	??2CA@@SAPAXI@Z				; CA::operator new
		add	esp, 4


		call	??0CA@@QAE@XZ				; CA::CA


		*/
		CA obj2;
		obj1.ObjectLocation();
		obj2.ObjectLocation();
		ptr1->ObjectLocation();
		ptr2->ObjectLocation();

		cout << "______________________________" << endl;
		CA *ptr = new CA[5];
		/*

		*/
		for (size_t i = 0; i < 5; i++)
		{
			(ptr + i)->ObjectLocation();
		}
	}
}