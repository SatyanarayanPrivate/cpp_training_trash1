#include<iostream>
#include<map>
using namespace std;
namespace nm29
{
	class CA
	{
		int *i;
		CA() :i(new int(100)){
			cout << "CA Ctor " << endl;
		}
		CA(const CA& objRef) :i(objRef.i){
		}
		CA & operator=(CA & objRef){
			i = objRef.i;
			return *this;
		}
		~CA(){
			cout << "CA Dtor " << endl;
			delete i;
		}
		static CA * CreateCA()//factory or creator
		{
			return new CA();
		}
		static void ReleaseCA(CA * pt){
			delete pt;
		}
	public:
		void FunCA(){
			cout << "Fun CA" << endl;
		}
		friend class SmartPointer;
	};

	class SmartPointer
	{
		CA *ptr;
		static map<CA*, int> MyMap;
		/*static void* operator new(size_t size)
		{
		return NULL;
		}
		static void* operator new[](size_t size)
		{
		return NULL;
		}
		static void operator delete(void *)
		{
		}
		static void operator delete[](void *)
		{
		}*/
	public:

		SmartPointer() :ptr(CA::CreateCA())
		{
			MyMap[ptr] = 1;
		}
		SmartPointer(SmartPointer & objRef) :ptr(objRef.ptr)
		{
			int count = MyMap[ptr];
			MyMap[ptr] = count + 1;
		}
		CA * operator->()
		{
			return ptr;
		}
		SmartPointer & operator=(SmartPointer & objRef)
		{
			if (ptr != objRef.ptr)
			{
				this->SmartPointer::~SmartPointer();
				this->SmartPointer::SmartPointer(objRef);

			}
			return *this;
		}
		~SmartPointer()
		{
			int count = MyMap[ptr] - 1;
			MyMap[ptr] = count;
			if (count == 0)
			{
				CA::ReleaseCA(ptr);
				MyMap.erase(ptr);
			}
		}
	};
	map<CA*, int> SmartPointer::MyMap;

	void main()
	{


		SmartPointer smt1;

		SmartPointer smt2;

		SmartPointer smt4;
		smt1 = smt4;

		SmartPointer smt3(smt1);

		smt1->FunCA();
	}
}