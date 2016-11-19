#include <iostream>
#include <map>
using namespace std;

//dofactory.com
//GRASP:: 16 principles

// iterator design pattern
#if 0
#define ARRAY_SIZE 5
class MyArray {
	//int arr[5]{1,2,3,4,5];	// c++11 for VC wont work
	int arr[ARRAY_SIZE];
	int index = 0x00;
public:
	MyArray() {
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		arr[3] = 4;
		arr[4] = 5;
	}
	void Reset() {
		index = 0;
	}
	int Next() {
		return arr[index ++];
	}
	bool HasNext() {

		return index<=5;
	}
	int First() {
		Reset();
		return Next();
	}
	void ForEach(void (*FPTR)(int )) {
		for (int it = First(); HasNext(); it = Next()) {
			FPTR(it);
		}
	}
};

void GetElement(int val) {
	cout << val << endl;
}

void main() {
	MyArray obj;
	obj.ForEach(GetElement);
}
#endif
#if 0
#define ARRAY_SIZE 5
class MyArray {
	//int arr[5]{1,2,3,4,5];	// c++11 for VC wont work
	int arr[ARRAY_SIZE];
	int len = ARRAY_SIZE;
public:
	MyArray() {
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		arr[3] = 4;
		arr[4] = 5;
	}
	MyArray & Begin() {
		return *this;
	}
	// nested class are implicit friends
	class Iterator {
		int *arr;
		int len;
		int index = 0x00;
	public:
		Iterator(MyArray &obj): arr(obj.arr), len(obj.len) {
			
		}

		void Reset() {
			index = 0;
		}
		int Next() {
			return arr[index++];
		}
		bool HasNext() {

			return index <= len;
		}
		int First() {
			Reset();
			return Next();
		}
		void ForEach(void(*FPTR)(int)) {
			for (int it = First(); HasNext(); it = Next()) {
				FPTR(it);
			}
		}
	};
};

void GetElement(int val) {
	cout << val << endl;
}

void main() {
	MyArray obj;
	MyArray::Iterator itr = obj.Begin();
	itr.ForEach(GetElement);
	for (int it = itr.First(); itr.HasNext(); it = itr.Next()) {
		cout << it << endl;
	}
}
#endif
#if 0
#define ARRAY_SIZE 5
class MyArray {
	//int arr[5]{1,2,3,4,5];	// c++11 for VC wont work
	int arr[ARRAY_SIZE];
	int len = ARRAY_SIZE;
public:
	MyArray() {
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		arr[3] = 4;
		arr[4] = 5;
	}
	MyArray & Begin() {
		return *this;
	}
	class Helper {
		MyArray *ptr;
		int index;
	public:
		Helper(MyArray *ptr, int index): ptr(ptr), index(index) {
		}
		// lazy load method
		Helper & operator=(int val) {
			cout << "writting" << endl;
			this->ptr->arr[index] = val;
			return *this;
		}
		operator int() {
			cout << "Reading" << endl;
			return this->ptr->arr[index];
		}
		Helper & operator=(Helper hlp) {
			cout << "reading/writting" << endl;
			this->ptr->arr[index] = hlp.ptr->arr[hlp.index];
			return *this;
		}
	};
	Helper & operator[] (int index) {
		//return arr[index];
		return Helper(this, index);
	}

	// nested class are implicit friends
	class Iterator {
		int *arr;
		int len;
		int index = 0x00;
	public:
		Iterator(MyArray &obj) : arr(obj.arr), len(obj.len) {

		}

		void Reset() {
			index = 0;
		}
		int Next() {
			return arr[index++];
		}
		bool HasNext() {

			return index <= len;
		}
		int First() {
			Reset();
			return Next();
		}
		void ForEach(void(*FPTR)(int)) {
			for (int it = First(); HasNext(); it = Next()) {
				FPTR(it);
			}
		}
	};
};

void GetElement(int val) {
	cout << val << endl;
}

void main() {
	MyArray obj;
	//obj[3] = 123;	// writing:: idempotent:: change state 
	int k = obj[2];	// reading:: nullipotent:: leaves state as it is
	//obj[1] = obj[0]; //read/write:: idempotent
	//cout << "k = " << k << endl;

	MyArray::Iterator itr = obj.Begin();
	itr.ForEach(GetElement);
	for (int it = itr.First(); itr.HasNext(); it = itr.Next()) {
		cout << it << endl;
	}
}
#endif
//ORM:: object relational mapper
//onion architechture

namespace adaptor_design {
// adaptor design pattern
	class KeyboardEvents {
	public:	
		void ReturnKeyPress() {
			cout << "Enter KeyPressed" << endl;
		}
	};
}


// observer desig pattern
// containments are always better than inheritance

//command pattern (compensation)

//Momento:: Maintain persistance of state of object
map<string, map<string, string> > Mymap; //before C++11
map<string, map<string, string>> Mymap; //C++11, multiple maps

//visitor::                                                                                                                                                                                                                                                     variation of algorothim for object hierarchy

void main() {

}

