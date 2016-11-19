#include<iostream>
#include<map>
using namespace std;
namespace nm41
{
	class Register
	{
	protected:
	}reg;
	class Employee
	{
		static map<int, Employee*> objectPool;
	protected:
		Employee()
		{
		}
		Employee(int key, Register &d)
		{
			objectPool[key] = this;
		}
	public:
		virtual Employee*  Clone() = 0;
		virtual void  Dojob() = 0;
		static Employee* CreateEmp(int key)
		{
			return objectPool[key]->Clone();
		}
		virtual ~Employee()
		{
			cout << "Employee Dtor " << endl;
		}
	};
	map<int, Employee*> Employee::objectPool;

	class Manager :public Employee
	{
	public:
		Manager()
		{

		}
		Manager(Manager & man)
		{
			//memberwise 
		}
		Manager(int key, Register & r) :Employee(key, r)
		{
			cout << "Manager getting pooled " << endl;
		}
		Employee*  Clone()
		{
			cout << "Manager Getting cloned" << endl;
			return new Manager(*this);
		}
		void  Dojob()
		{
			cout << "Manager job done " << endl;
		}
		~Manager()
		{
			cout << "Manager Dtor " << endl;
		}

	};// man(10, reg);

	class Tester :public Employee
	{
	public:
		Tester()
		{

		}
		Tester(Tester & test)
		{

		}
		Tester(int key, Register & r) :Employee(key, r)
		{
			cout << "Tester getting pooled " << endl;
		}
		Employee*  Clone()
		{
			cout << "Tester Getting cloned" << endl;
			return new Tester(*this);
		}
		void  Dojob()
		{
			cout << "Tester job done " << endl;
		}
		~Tester()
		{
			cout << "Tester Dtor " << endl;
		}
	};// tester(20, reg);

	class Developer :public Employee
	{
	public:
		Developer()
		{

		}
		Developer(Developer & dev)
		{

		}
		Developer(int key, Register & r) :Employee(key, r)
		{
			cout << "Developer getting pooled " << endl;
		}
		Employee*  Clone()
		{
			cout << "Developer Getting cloned" << endl;
			return new Developer(*this);
		}
		void  Dojob()
		{
			cout << "Developer job done " << endl;
		}
		~Developer()
		{
			cout << "Developer Dtor " << endl;
		}
	};// dev(30, reg);

	void main()
	{
		cout << "________________________" << endl;
		Employee *emp = Employee::CreateEmp(10);
		cout << "________________________" << endl;
		emp->Dojob();
		cout << "________________________" << endl;
		delete emp;
		cout << "________________________" << endl;
	}
}