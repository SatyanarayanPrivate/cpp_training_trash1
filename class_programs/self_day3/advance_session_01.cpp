#include <iostream>
using namespace std;

namespace smart_pointer {
	class CA {
		int *i;
	public:
		CA(): i(new int(100))
		{
			cout << "CA ctor" << endl;
		}
		void FuncCA () {
			cout << "FuncCA" << endl;
		}
		~CA() {
			cout << "CA ctor" << endl;
			delete i;
		}
	};

	void main()
	{
		CA obj1;
		CA obj2;

		obj1 = obj2;
	}
}
namespace smart_pointer1 {
	//smart should be on stack and its contents should be on heap
	//smart pointer should always overloaded with "->"
	class CA {
		int *i;
		CA() : i(new int(100))
		{
			cout << "CA ctor" << endl;
		}
		~CA() {
			cout << "CA ctor" << endl;
			delete i;
		}
	public:

		void FuncCA() {
			cout << "FuncCA" << endl;
		}
		static CA *CreateCA() {
			return new CA();
		}
		static void ReleaseCA(CA* ptr) {
			delete ptr;
		}
	};

	class SmartPointer {
		CA *ptr;
	public:
		SmartPointer() : ptr(CA::CreateCA()) {

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
		CA *ptr = CA::CreateCA();
		CA::ReleaseCA(ptr);

		// smart pointer
		//SmartPointer smt1;
		//SmartPointer *smt1 = new SmartPointer();	// this lead to memory leak smartpointer should be only on stack
	}
}


class SmartPointer;
class CA {
	int *i;
	CA() : i(new int(100))
	{
		cout << "CA ctor" << endl;
	}
	CA(const CA&objRef) : i(new int(*objRef.i)) {

	}
	CA & operator= (CA & objRef) {
		*i = *objRef.i;
		return *this;
	}
	~CA() {
		cout << "CA ctor" << endl;
		delete i;
	}
	static CA *CreateCA() {
		return new CA();
	}
	static void ReleaseCA(CA* ptr) {
		delete ptr;
	}
	
public:
	void FuncCA() {
		cout << "FuncCA" << endl;
	}
	friend class SmartPointer;
};

class SmartPointer {
	CA *ptr;
public:
	SmartPointer() : ptr(CA::CreateCA()) {
	}
	~SmartPointer()	{
		CA::ReleaseCA(ptr);
	}

	SmartPointer(SmartPointer &objRef) : ptr(new CA(*objRef.ptr)) {

	}
	CA *operator->() {
		return ptr;
	}

	SmartPointer & operator= (SmartPointer &objRef) {
		*ptr = *objRef.ptr;
		return *this;
	}
};


void main (){
	SmartPointer smt1;
	SmartPointer smt2;
	smt1 = smt2;	// deep copy while assignment
	SmartPointer smt3(smt1);	// deep copy while copyconstructor

}

// shallow copy 
// unique pointer	(changing owernship)
// shared pointer	(using map maintain reference_count)