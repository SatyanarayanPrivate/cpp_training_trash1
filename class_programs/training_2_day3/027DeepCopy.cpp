#include<iostream>
using namespace std;
namespace nm27{
	class CA
	{
		int *i;
		CA() :i(new int(100)){
			cout << "CA Ctor " << endl;
		}
		CA(const CA& objRef) :i(new int(*objRef.i)){
		}
		CA & operator=(CA & objRef){
			*i = *objRef.i;
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
		static void* operator new(size_t size)
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
		}
	public:
		SmartPointer() :ptr(CA::CreateCA())
		{

		}
		SmartPointer(SmartPointer & objRef) :ptr(new CA(*objRef.ptr))
		{
		}
		CA * operator->()
		{
			return ptr;
		}
		SmartPointer & operator=(SmartPointer & objRef)
		{
			*ptr = *objRef.ptr;
			return *this;
		}
		~SmartPointer()
		{
			CA::ReleaseCA(ptr);
		}
	};

	void main()
	{
		//CA obj1;
		//CA obj2;
		//obj1 = obj2;
		//CA *ptr = new CA();
		//CA *ptr = CA::CreateCA();

		//delete ptr;
		//	CA::ReleaseCA(ptr);
		//SmartPointer *smt1 = new SmartPointer();

		SmartPointer smt1;

		SmartPointer smt2;
		smt1 = smt2;

		SmartPointer smt3(smt1);

		smt1->FunCA();
	}
}