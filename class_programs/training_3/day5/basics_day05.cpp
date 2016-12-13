#include <iostream>
#include <string>
#include <map>
#include <typeinfo>
using namespace std;

/*
- callback
    -
- member access resolution class::memberfunction
- pre and post increment on smart pointers
    - operator++(int para){}:: for post increment
    - operator++(){}:: for pre increment
- Books
    - scott meyer
        - effective c++
        - more effective c++
        - effective STL
        - effective modern c++
    - James Coplein
        - Advance C++
    - Stanley Lippman
        - Inside C++ object model.
    - FAQ's in c++
- Template (generic)
    - for all c++ compiler:: template is compile time concept
- RTTI: Run time type identification
- nice class: which contains
    - Default Ctor
    - copy ctor
    - all comparison operator overloaded
    - assignment operator overloaded
- STL always accepts only Nice class only.
Template
    -
    - template specializations
    -   template<>
        class Stack<int>.{};
    - template with default argument
        - template<typename T=double>
        - template<typename T=double, int size=5>
    - partial spetialization
        -

*/


namespace basic_callback {
class Employee
{
    int x;
    int y;
    int z;
public:
    Employee (int x, int y, int z): x(x), y(y), z(z) {}
    void fun1 () {
        cout << "fun1 called" << endl;
    }
    void fun2 () {
        cout << "fun2 called" << endl;
    }
};

void VendorBusiness(Employee &emp, void (Employee:: *fp)()) {
    cout << "vendor 10000 start" << endl;
    (emp.*fp)();
    cout << "vendor 20000 stop" << endl;
    cout << "----------------------" << endl;
}
void VendorBusiness(Employee *emp, void (Employee:: *fp)()) {
    cout << "vendor 10001 start" << endl;
    (emp->*fp)();
    cout << "vendor 20001 stop" << endl;
    cout << "----------------------" << endl;
}

int main () {
    Employee emp(10,20,30);
    VendorBusiness(emp,&Employee::fun1);

    Employee emp1(11,21,31);
    VendorBusiness(&emp,&Employee::fun2);

    return 0;
}
}

namespace operator_overloading_smart_pointer {
class SmrtPtr;
class Employee
{
    int x;
    int y;
    int z;

    Employee(): x(0), y(0), z(0) {
    }
    ~Employee(){
    }
    Employee * operator->() {

        return this;
    }
    friend class SmrtPtr;
public:
    void fun1 () {
        cout << "fun1 called" << endl;
    }
    void fun2 () {
        cout << "fun2 called" << endl;
    }
};

typedef void (Employee::*FPTR)();

class SmrtPtr {
    Employee *_ptr;
    FPTR _fp;
public:
    SmrtPtr(): _ptr(new Employee()), _fp(NULL) {
    }
    Employee * operator->() {
        return _ptr;
    }

    SmrtPtr & operator->*(FPTR fp) {
        _fp = fp;
        return *this;
    }
    void operator()() {
        (_ptr->*_fp)();
        //(_ptr->operator->()->*_fp)();
    }

    Employee * operator++(int val)        // for post increament:: val is unused
    {
        cout << "Post Increment Value:: "<< val << endl;

        return _ptr;
    }
    Employee * operator++()        // for pre increament
    {
        cout << "Pre Increment" << endl;

        return _ptr;
    }
    operator Employee*()
    {
        return _ptr;
    }
    operator void*()
    {
        return _ptr;
    }
    explicit operator void**()  // explicit:: compiler demands to use casting
    {
        return (void **)&_ptr;
    }
    ~SmrtPtr() {
        delete _ptr;
    }
};

void ConsumerBusiness(SmrtPtr &ptr, FPTR fp) {
    cout << "Consumer job started" << endl;
    (ptr->*fp)();   // need to define operator ->* and operator() in class SmrtPtr
    cout << "Consumer job completed" << endl;
    cout << "----------------------" << endl;
}
int main ()
{
    class SmrtPtr obj;
    ConsumerBusiness (obj, &Employee::fun1);
    obj++;
    ++obj;

    Employee *p = obj;
    void *p1 = obj;
    void **p2 = (void **)obj;   // explicit:: compiler demand to use casting
    return 0;
}
}

//problem:: (arr[i][j]->*fp)()
namespace basic_niceclass {
// nice class
class Employee {
    int _eId;
    string _eName;
public:
    Employee(int eid=0, string ename=""): _eId(eid), _eName(ename) {}
    Employee(const Employee &ObjRef): _eId(ObjRef._eId), _eName(ObjRef._eName) {}
    Employee& operator= (const Employee &ObjRef) {
        _eId = ObjRef._eId;
        _eName = ObjRef._eName;
        return *this;
    }

    friend ostream & operator<< (ostream &os, Employee &ObjRef){
        os << "Employee with ID:: " << ObjRef._eId << " Name:: " << ObjRef._eName;
        return os;
    }
    bool operator<= (const Employee &ObjRef) {
        return _eId <= ObjRef._eId;
    }
    bool operator>= (const Employee &ObjRef) {
        return _eId >= ObjRef._eId;
    }
    bool operator< (const Employee &ObjRef) {
        return _eId < ObjRef._eId;
    }
    bool operator> (const Employee &ObjRef) {
        return _eId > ObjRef._eId;
    }
    bool operator== (const Employee &ObjRef) {
        return _eId == ObjRef._eId;
    }
    bool operator!= (const Employee &ObjRef) {
        return _eId != ObjRef._eId;
    }
};

template<typename T=double, int size=5> // default argument with const size value 5 which is used for array size

class Stack {
    T _arr[size];
    int _top;
public:
    Stack (): _top(-1){
        cout << "Stack Created for (" << typeid(T).name() << ")"<< endl;
    }
    void Push(T para) {
        _arr[++_top] = para;
    }
    T Pop() {
        return _arr[_top--];
    }
    T Peek() {
        return _arr[_top];
    }
    bool IsEmpty() {
        return _top == -1;
    }
    bool IsFull() {
        return _top == (size-1);
    }
    void Sort() {
        for (int i = 0;i<_top;i++) {
            for (int j = i + 1;j <= _top;j++) {
                if (_arr[i] >= _arr[j]) {
                    T temp = _arr[i];
                    _arr[i] = _arr[j];
                    _arr[j] = temp;
                }
            }
        }
    }
    void List () {
        for (int i = _top; i >= 0; i--) {
            cout <<  _arr[i] << endl;
        }
    }
};
template<int size>
class Stack<int, size> {
    int _arr[size];
    int _top;
public:
    Stack (): _top(-1){
        cout << "Stack Specialization Created for (" << typeid(int).name() << ")"<< endl;
    }
    void Push(int para) {
        _arr[++_top] = para;
    }
    int Pop() {
        return _arr[_top--];
    }
    int Peek() {
        return _arr[_top];
    }
    bool IsEmpty() {
        return _top == -1;
    }
    bool IsFull() {
        return _top == (size-1);
    }
    void Sort() {
        for (int i = 0;i<_top;i++) {
            for (int j = i + 1;j <= _top;j++) {
                if (_arr[i] >= _arr[j]) {
                    int temp = _arr[i];
                    _arr[i] = _arr[j];
                    _arr[j] = temp;
                }
            }
        }
    }
    void List () {
        for (int i = _top; i >= 0; i--) {
            cout <<  _arr[i] << endl;
        }
    }
};

int main1 () {
    //Stack<double> st1;
    Stack<int,10> st;   //size value set to 10
    Stack<> st1;    // default type used
    st.Push(10);
    st.Push(9);
    st.Push(7);
    st.Push(76);
    st.List();
    //cout << "Pop:: " << st.Pop() << endl;
    cout << "--------------------------------------------" << endl;
    st.Sort();
    st.List();
    return 0;
}

int main () {
    Employee emp1 (101, "sachin1");
    Employee emp4 (102, "sachin2");
    Employee emp2 (103, "sachin3");
    Employee emp3 (104, "sachin4");

    Stack<Employee> st2;
    st2.Push(emp1);
    st2.Push(emp2);
    st2.Push(emp3);
    st2.Push(emp4);
    st2.List();
    cout << "--------------------------------------------" << endl;
    st2.Sort();
    st2.List();
    cout << "--------------------------------------------" << endl;
    return 0;
}
}

namespace problem_generic_smartpointer {
//problem:: generic smart pointer
template<typename T>
class GenericSmartPtr {
    T *_ptr;
    static map<T*, int> MyMap;
public:
    GenericSmartPtr (): _ptr(new T()) {
        MyMap[_ptr] = 1;
    }
    void DummyCopyCtor(const GenericSmartPtr &ObjRef){
        _ptr = ObjRef._ptr;
        MyMap[_ptr]++;
    }
    T* operator->() {
        return _ptr;
    }
    GenericSmartPtr(const GenericSmartPtr &ObjRef):_ptr(ObjRef._ptr) {
        MyMap [_ptr]++;
    }
    GenericSmartPtr& operator=(const GenericSmartPtr &ObjRef) {
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

    ~GenericSmartPtr() {
        int count= MyMap[_ptr];
        MyMap[_ptr] = --count;
        if (count == 0x00) {
            MyMap.erase(_ptr);
            delete _ptr;
        }
    }
};
template<typename T>
map<T*, int> GenericSmartPtr<T>::MyMap;

int main () {
    GenericSmartPtr<double> sm1;

    GenericSmartPtr<int> sm2;
    /*GenericSmartPtr<int> sm3;
    GenericSmartPtr<int> sm4 = sm3;
    sm2 = sm1;
    */
    return 0;
}
}


int main ()
{
    return 0;
}
