#include <iostream>
#include <map>
using namespace std;


namespace protype_pattern {
#if 0
	//Prototype
	class Register {
	protected:
	};

	class Employee {
		static map<int, Employee*> ObjectPool;
	protected:
		Employee()
		{

		}
		Employee(int key, Register $d)
		{
			ObjectPool[key] = this;
		}
	public:
		virtual Employee* Clone() = 0;
		virtual void DoJob() = 0;
		static Employee *CreateEmp(int key) {
			return ObjectPool[key]->Clone();
		}

	};

	map<int, Employee*> Employee::ObjectPool;

	class Manager : public Employee {
	public:
		Manager()
		{

		}
		Manager(Manager &man)
		{

		}
		Manager(int key, Register &d) : Employee(key, r)
		{
			cout << "Manager Getting Pooled" << endl;
		}
		Employee* Clone() {
			cout << "Manager Getting cloned" << endl;
		}
		void Dojob() {
			cout << "Manager Job Done" << endl;
		}
	}man(10, reg);

	class Tester : public Employee {
	public:
		Tester()
		{

		}
		Tester(Tester &test)
		{

		}
		Tester(int key, Register &d) : Employee(key, r)
		{
			cout << "Tester Getting Pooled" << endl;
		}
		Employee* Clone() {
			cout << "Tester Getting cloned" << endl;
			return new Tester(*this);
		}
		Dojob() {
			cout << "Tester Job Done" << endl;
		}
	};

	class Developer : public Employee {
	public:
		Developer()
		{

		}
		Developer(Developer &test)
		{

		}
		Developer(int key, Register &d) : Employee(key, r)
		{
			cout << "Developer Getting Pooled" << endl;
		}
		Employee* Clone() {
			cout << "Developer Getting cloned" << endl;
			return new Developer(*this);
		}
		Dojob() {
			cout << "Developer Job Done" << endl;
		}
	};
#endif
}

// state pattern


// Default Ctor
/*
- base has Ctor and derived has dont have ctor
- when have virtual function in base class 
- contained object has Ctor
- virual base class
*/

// 
/*
setvptr present in prolog of Dtor and Ctor
- base has Dtor and derived has dont have Dtor
- 
*/

// horizontal access control vs vertical access control
void main() {

}