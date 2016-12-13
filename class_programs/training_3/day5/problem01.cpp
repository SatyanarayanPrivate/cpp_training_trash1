//problem01:: (arr[i][j]->*fp)()
//problem02:: generic smart pointer
//problem03:: track objects created on heap
#include <iostream>
#include <string>
#include <map>
#include <typeinfo>
using namespace std;


namespace problem01 {
class SmrtPtr;
class Employee
{
    int x;
    int y;
    int z;
    Employee(): x(0), y(0), z(0) {
        cout << "CA Default Ctor" << endl;
    }
    ~Employee(){
        cout << "CA Dtor" << endl;
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
#define ARR_LEN 3
class SmrtPtr {
    Employee *_ArrEmpPtr[ARR_LEN][ARR_LEN];
    FPTR _fp;
public:
    SmrtPtr(): _fp(NULL) {
        for (int i =0;i < ARR_LEN;i++) {
            for (int j =0;j < ARR_LEN;j++){
                _ArrEmpPtr[i][j] = new Employee();
            }
        }
    }
    class HelperOuter {
        SmrtPtr *_OuterSmrtPtr;
        int _RIndex;
        int _CIndex;
    public:
        HelperOuter(SmrtPtr * OuterSmrtPtr, int RIndex, int CIndex= 0x00): _OuterSmrtPtr(OuterSmrtPtr), _RIndex(RIndex), _CIndex(CIndex) {}
        class HelperInner
        {
            HelperOuter *_OuterHelper;
        public:
            HelperInner(HelperOuter* OuterHelper): _OuterHelper(OuterHelper) {}

            HelperInner &operator->*(FPTR fp) {
                _OuterHelper->_OuterSmrtPtr->_fp = fp;
                return *this;
            }
            void operator()(){
                (_OuterHelper->_OuterSmrtPtr->_ArrEmpPtr[_OuterHelper->_RIndex][_OuterHelper->_CIndex]->*_OuterHelper->_OuterSmrtPtr->_fp)();
            }
        };
        HelperInner operator[] (int CIndex) {
            _CIndex = CIndex;
            return HelperInner(this);
        }
    };
    HelperOuter operator[](int RIndex){
        return HelperOuter(this, RIndex);
    }
    ~SmrtPtr() {
        for (int i =0;i < ARR_LEN;i++) {
            for (int j =0;j < ARR_LEN;j++){
                delete _ArrEmpPtr[i][j];
            }
        }
    }
};

void ConsumerBusiness(SmrtPtr &ptr,int RIndex, int CIndex, FPTR fp) {
    cout << "Consumer job started" << endl;
    (ptr[RIndex][CIndex]->*fp)();   // need to define operator ->* and operator() in class SmrtPtr
    cout << "Consumer job completed" << endl;
    cout << "----------------------" << endl << endl;
}
int main () {
    class SmrtPtr obj;
    cout << "----------------------" << endl<< endl;
    ConsumerBusiness (obj, 0, 0,&Employee::fun2);
    return 0;
}
}


#if 0
namespace problem02 {
class Employee {
    int x;
    int y;
    int z;
    Employee(): x(0), y(0), z(0) {
        cout << "CA Default Ctor" << endl;
    }
    ~Employee(){
        cout << "CA Dtor" << endl;
    }
public:
    void fun1 () {
        cout << "fun1 called" << endl;
    }
    void fun2 () {
        cout << "fun2 called" << endl;
    }
    friend class GenericSmartPtr;
};

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
    //GenericSmartPtr<Employee> sm3;
    return 0;
}
}
#endif
template<typename TYPE>
class CreateObject {
    bool _IsOnHeap;
    static bool _HeapFlag;
    static size_t _HeapObjCount;
public:
    static int _HeapCount;
    CreateObject (): _IsOnHeap(_HeapFlag) {
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
        _HeapObjCount += 1;
        return malloc(size);
    }
    void *operator new[](size_t size) {
        _HeapFlag = true;
        _HeapCount = (size-8 / sizeof(CreateObject)); // 8 value depends upon compiler
        return malloc(size);
    }
    void operator delete(void *ptr) {
        delete ptr;
    }
    ~CreateObject () {

    }
};
template<typename T>
size_t CreateObject<T>::_HeapObjCount = 0;

int main () {

    return 0;
}
