#include <iostream>
using namespace std;

namespace singleton {
#if 0
	// Singleton
	class Smart;
	class CA {
		CA() {
			cout << "CA ctor" << endl;
		}
		~CA() {
			cout << "CA Dtor" << endl;
		}
		static CA *head;
		static CA* CreateCA() {
			if (head == NULL) {
				head = new CA();
				return head;
			}
		}
		static void ReleaseCA() {
			delete head;
			head = NULL;
		}
	public:
		void fun(void) {
			cout << "CA fun" << endl;
		}
		friend class Smart;
	};

	CA* CA::head = NULL;

	class Smart {
		CA *ptr;
		static int count;
	public:
		Smart() : ptr(CA::CreateCA()) {
			count++;
		}
		CA* operator->() {
			return ptr;
		}
		~Smart() {
			count--;
			if (count == 0) {
				CA::ReleaseCA();
			}
		}
	};

	int Smart::count = 0;

	void main() {
		Smart smt1;
		Smart smt2;
		Smart smt3;
		smt1->fun();
	}
#endif
}


namespace object_location {
// object location1

// new operator
//custom new
//placement new
//no throuw new
//normal through

	// after new() ctor gets called
#if 0
	class CA {
		bool IsOnHeap = false;
		static bool GlobalHeap;
	public:
		CA() : IsOnHeap(GlobalHeap)
		{
			GlobalHeap = false;
			cout << "CA ctor" << endl;
		}
		~CA()
		{
			cout << "CA Dtor" << endl;
		}

		//by default operators fun's are static
		static void * operator new(size_t size) {
			//IsOnHeap = true;	// as IsOnheap is not static
			cout << "CA new" << endl;
			void *pt = malloc(size);
			GlobalHeap = true;
			//((CA*)pt)->IsOnHeap = true;
			return malloc(size);
		}

		void ObjectLocation() {
			if (IsOnHeap == true) {
				cout << "object is on heap" << endl;
			}
			else {
				cout << "object is not on heap" << endl;
			}
		}
	};
	bool CA::GlobalHeap = false;
	void main() {
		CA obj1;
		CA obj2;
		CA *ptr1 = new CA();
		// after new operator it will get called to CA::CA
		CA *ptr2 = new CA();

		obj1.ObjectLocation();
		obj2.ObjectLocation();
		ptr1->ObjectLocation();
		ptr2->ObjectLocation();
	}
#endif
#if 0

	class CA {
		bool IsOnHeap = false;
		static bool GlobalHeap;
		static int GlobalCount;
	public:
		CA() : IsOnHeap(GlobalHeap)
		{
			GlobalCount--;
			if (GlobalCount <= 0x00)
				GlobalHeap = false;
			cout << "CA ctor" << endl;
		}
		~CA()
		{
			cout << "CA Dtor" << endl;
		}

		//by default operators fun's are static
		static void * operator new(size_t size) {
			//IsOnHeap = true;	// as IsOnheap is not static
			cout << "CA new" << endl;
			void *pt = malloc(size);
			GlobalHeap = true;
			return malloc(size);
		}
		static void * operator new[](size_t size) {
			cout << "CA new[]" << endl;
			void *pt = malloc(size);
			GlobalHeap = true;
			GlobalCount = size / sizeof(CA);
			return malloc(size);
		}

			void ObjectLocation() {
			if (IsOnHeap == true) {
				cout << "object is on heap" << endl;
			}
			else {
				cout << "object is not on heap" << endl;
			}
		}
	};
	bool CA::GlobalHeap = false;
	int CA::GlobalCount = 0x00;
	void main() {
		CA obj1;
		CA obj2;
		CA *ptr1 = new CA();
		// after new operator it will get called to CA::CA
		CA *ptr2 = new CA();

		obj1.ObjectLocation();
		obj2.ObjectLocation();
		ptr1->ObjectLocation();
		ptr2->ObjectLocation();

		cout << "--------------------------------\n" << endl;
		CA *ptr = new CA[5];
		for (size_t i = 0x00; i < 5; i++) {
			(ptr + i)->ObjectLocation();
		}
	}
#endif
}


namespace exception_handling {
	// exception handling
	void Release() {
		cout << "resources released in Release()" << endl;
		exit(0);
	}
	void main1() {
		set_terminate(Release);		//register termiante method
		cout << "resources alloted in main" << endl;
		throw 100;
		cout << "resources released in main" << endl;
	}

	void fun() {
		cout << "apple" << endl;
		throw 100.2;
		cout << "orange" << endl;
	}

	void main2() {
		cout << "pine" << endl;
		try {
			fun();
		}
		catch (int exp) {
			cout << "int exp= " << exp << endl;
		}
		catch (double exp) {
			cout << "double exp= " << exp << endl;
		}
		cout << "jack" << endl;
	}
#if 0
	class CA {
	public:
		CA() {
			cout << "CA ctor" << endl;
		}
		CA(CA &objref) {
			cout << "CA CCtor" << endl;
		}

		~CA() {
			cout << "CA dtor" << endl;
		}
	};

	void fun1() {
		cout << "apple" << endl;
		throw 100.2;
		cout << "orange" << endl;
	}
	/*
	creates catch table per try block
	- thrown information copied to catch table
	- local variable gets released
	- exception copied to catch block
	*/
	void main() {
		//CA obj;
		cout << "pine" << endl;
		try {
			CA obj1;
			throw obj1;
			fun1();
		}
		catch (int exp) {
			cout << "int exp= " << exp << endl;
		}
		catch (double exp) {
			cout << "double exp= " << exp << endl;
		}
		catch (CA obj) {
			cout << "CA exp= " << endl;
		}
		cout << "jack" << endl;
	}
#endif
#if 0
	class CA {
	public:
		CA() {
			cout << "CA ctor" << endl;
		}
		CA(CA &objref) {
			cout << "CA CCtor" << endl;
		}

		~CA() {
			cout << "CA dtor" << endl;
			throw 100;	// never throw exceptions from Dtor
		}
	};

	void fun1() {
		cout << "apple" << endl;
		throw 100.2;
		cout << "orange" << endl;
	}
	/*
	//exception overlaping can not be handled
	*/
	void main() {
		//CA obj;
		cout << "pine" << endl;
		try {
			CA obj1;
			throw obj1;
			fun1();
		}
		catch (int exp) {
			cout << "int exp= " << exp << endl;
		}
		catch (double exp) {
			cout << "double exp= " << exp << endl;
		}
		catch (CA obj) {
			cout << "CA exp= " << endl;
		}
		cout << "jack" << endl;
	}


	void main() {
		try {

			try {
				//throw 100.34;
				//throw 100;
				throw "100";
			}
			//catch (int exp) {
			catch (int & exp) {
				exp += 100;
				cout << "int exp= " << exp << endl;
				throw;	// rethrow
			}
			catch (double exp) {
				cout << "double exp= " << exp << endl;
				throw 200;
			}
			catch (...) //catch any// catch all //general exception
			{
				cout << "general exp= " << endl;
			}
		}
		catch (int param) {
			cout << "outer excep int " << param << endl;
		}
	}

#endif

	class CA {
	public:
		CA() {
			cout << "CA ctor" << endl;
			throw 100;	// avoid memory leaks if new fails
		}
		~CA() {
			cout << "CA dtor" << endl;
		}
	};

	void main() {
		CA *caPtr = NULL;

		try {
			caPtr = new CA();
			/*
			// expansion of above statement
			CA *temp=operator new(size){}
			try {
				temp->CA::CA();
			}
			catch (...) {
				free(temp)
				throw;
			}
			catPtr = temp;
			*/
		}
		catch (int exp) {
			cout << "int exp= " << exp << endl;
		}
		if (caPtr == NULL) {
			cout << "apple" << endl;
		}
		else {
			cout << "orange" << endl;
			delete caPtr;
		}
	}
}



void main() {

}