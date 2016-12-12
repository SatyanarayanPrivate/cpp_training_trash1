#include <iostream>
#include <string>
#include <map>
using namespace std;

/*
- Creator or Factory
    - controlling creating object
    - produce service object
    - creator:: gives own class
    - factory:: gives other class
- Smart pointer
    - Manage memory
    - smart pointer should not be allowed on heap
    - samrt should be overlaoded with operator->().
- operator new and delete bydefault are static
- new / delete operator
    - Ctor gets called after operator new
    - delete gets called after Dtor
- ctor
    - default Ctor
    - copy ctor
    - paramter ctor
    - initializaer_list ctor
-
*/


namespace smartPointer_01 {
class EmployeeSmartPtr;

class Employee {
    int _eId;
    string _eName;

    Employee (int eId = 0x00, string eName = ""): _eId(eId), _eName(eName) {
        cout << "Employee Default Ctor" << endl;
    }

    ~Employee () {
        cout << "Employee Dctor" << endl;
    }

    // Creator (Factory)
    static Employee * CreateEmployee() {
        // logging business
        return new Employee();
    }
    static void ReleaseEmployee(Employee *ptr) {
        delete ptr;
    }

public:
    void DoEmpBusiness() {
        cout << "Business done for ID:: " << _eId << " with Name:: " << _eName << endl;
    }
    friend class EmployeeSmartPtr;
};

class EmployeeSmartPtr
{
    Employee *_empPtr;

    static void* operator new (size_t size) {
        return NULL;
    }
    static void operator delete (void *) {
    }
    void* operator new [](size_t size) {
        return NULL;
    }
    void operator delete [](void *) {
    }
public:
    EmployeeSmartPtr (): _empPtr(Employee:: CreateEmployee()) {
    }
    ~EmployeeSmartPtr () {
        Employee::ReleaseEmployee(_empPtr);
    }
    Employee* operator->() {
        return _empPtr;
    }
};

int main () {
    //Employee obj1;
    //obj1.DoEmpBusiness();

    //Employee *ptr = Employee:: CreateEmployee();//new Employee ();
    //Employee:: ReleaseEmployee(ptr);

    EmployeeSmartPtr Sptr;
    //Sptr.operator->()->DoEmpBusiness();
    Sptr->DoEmpBusiness();

    return 0;
}
}

namespace bsics_new01 {
class CA
{
    bool _IsOnHeap;
    static bool _HeapFlag;

public:
    static int _HeapCount;
    CA (): _IsOnHeap(_HeapFlag)
    {
        _HeapCount--;
        if (_HeapCount <= 0) {
            _HeapFlag = false;
            _HeapCount = 0x00;
        }
    }
    void PrintLocation() {
        if (_IsOnHeap == true) {
            cout << "object is on heap" << endl;
        }
        else {
            cout << "object is not on heap" << endl;
        }
    }
    void *operator new(size_t size) {
        _HeapFlag = true;
        _HeapCount = (size / sizeof(CA));
        //cout << " _heap_count:: "<< "(" << size << " / " << sizeof(CA) << ") = "<< _HeapCount << endl;
        return malloc(size);
    }
    void *operator new[](size_t size) {
        _HeapFlag = true;
        _HeapCount = (size-8 / sizeof(CA)); // 8 value depends upon compiler
        //cout << " _heap_count:: "<< "(" << size << " / " << sizeof(CA) << ") = "<< _HeapCount << endl;
        return malloc(size);
    }

    ~CA () {
    }
};
bool CA::_HeapFlag = false;
int CA::_HeapCount = 0;
#define ARR_SIZE 5
int main ()
{
    CA obj;
    obj.PrintLocation();
    CA *ptr = new CA();
    ptr->PrintLocation();

    CA *ptr2 = new CA();
    ptr2->PrintLocation();

    CA *ptr1 = new CA[ARR_SIZE];
    int *pt = (int*)ptr1;
    cout << "array elements:: " << *(pt - 1) << endl;  // for vs:: stores number of array elements
    for (size_t i =0; i< ARR_SIZE; i++) {
        (ptr1 + i)->PrintLocation();
    }

    CA obj1;
    obj1.PrintLocation();
    delete ptr;
    delete[] ptr1;
    return 0;
}
}

// shared pointer
namespace shared_ptr_shalow_copy {
class SmrtPtr;
class CA
{
    int *ptr;

    CA():ptr(new int(10)) {
        cout << "CA Ctor" << endl;
    }
    ~CA () {
        cout << "CA Dtor" << endl;
        if (ptr != NULL)
            delete ptr;
    }
    CA (const CA &ObjRef): ptr(new int (*ObjRef.ptr)){
        cout << "CA Copy Ctor" << endl;
    }
    CA & operator= (const CA &ObjRef){
        return *this;;
    }
public:
    void fun () {
        cout << "fun " << endl;
    }
    friend class SmrtPtr;
};
class SmrtPtr {
    CA*_ptr;
    static map<CA*, int> MyMap;
public:
    SmrtPtr (): _ptr(new CA()) {
        MyMap[_ptr] = 1;
    }
    void DummyCopyCtor(const SmrtPtr &ObjRef){
        _ptr = ObjRef._ptr;
        MyMap[_ptr]++;
    }
    CA* operator->() {
        return _ptr;
    }
    SmrtPtr(const SmrtPtr &ObjRef):_ptr(ObjRef._ptr) {
        MyMap [_ptr]++;
    }
    SmrtPtr& operator=(const SmrtPtr &ObjRef) {
        if (_ptr != ObjRef._ptr) {
            DummyDtor();
            DummyCopyCtor(ObjRef);
        }
        return *this;
    }
    void DummyDtor() {
        int count= MyMap[_ptr];
        MyMap[_ptr] = --count;
        if (count == 0x00) {
            MyMap.erase(_ptr);
            delete _ptr;
        }
    }

    ~SmrtPtr() {
        int count= MyMap[_ptr];
        MyMap[_ptr] = --count;
        if (count == 0x00) {
            MyMap.erase(_ptr);
            delete _ptr;
        }
    }
#if 0
{
    SmrtPtr(SmrtPtr &ObjRef) {
        cout << "SM copy ctor" << endl;
        if (ObjRef._ptr != NULL) {
            _ptr = ObjRef._ptr;
            ObjRef._ptr = NULL;
        }
    }
    SmrtPtr& operator=(SmrtPtr &ObjRef){
        cout << "SM Operator= " << endl;
        if (ObjRef._ptr != NULL) {
            _ptr = ObjRef._ptr;
            ObjRef._ptr = NULL;
        }
        return *this;
    }
    ~SmrtPtr() {
        if (_ptr != NULL)
            delete _ptr;
    }
}
#endif
};
map<CA*, int> SmrtPtr ::MyMap;

int  main ()
{
    SmrtPtr sm1;
    sm1->fun();
    SmrtPtr sm2;
    SmrtPtr sm3;
    SmrtPtr sm4 = sm3;
    sm2 = sm1;
    return 0;
}
}
