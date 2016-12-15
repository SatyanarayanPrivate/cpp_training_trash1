#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>
#include <typeinfo>
using namespace std;

/*
- sizeof empty class 1byte
    - bcz to access this pointer

- virtual function
    - static array created in data segment:: vtable
        - which contains virtual functions address list.
    - vtable shared among all object.
    - vptr:: which holds vtable address.
    - object structure
        - every object has its own vptr.
        - other member are present at below vptr.
    - calling non virtual method
        - using object:: non virtual functions are directly resolved from code segment.
        - using reference variable:: non virtual functions are directly resolved from code segment.
        - using pointer:: non virtual functions are directly resolved from code segment.
    - calling virtual method
        - using object:: virtual functions are directly resolved from code segment.
        - using reference variable:: virtual functions are resolved via vtable.
        - using pointer:: virtual functions are resolved via vtable.
    - funtion type
        - overriding:: use override key to override virtual method in derived class
            - void fun() override
        - uppending:: adding new virtual method in derived class.
            - on overloading base virtual method in derived class that method get upppended in vtable of derived class
        - hidding:: derived class has method (non virtual method) with name of same as of base class.
    - calling ctor with container
        - call derived class ctor
        - derived class ctor's prolog
            - call to base class ctor
            - setvptr:: derived class vtable
            - container class ctor.
        - execute derived class ctor body
    - ctor and dtor
        - in prolog of ctor and dtor setvptr is called
- polymorphisam
    - run time polymorphisam:: lsp example
    - static time polymorphisam:: override
- multiple - inheritance
    - when derived class inherited from multiple class then
        - number of vtable is equal to number of base class
            - class CC:class CA, class CB
                - vtable's created vptr[0] and vptr[1] for class CA and class CB respectively.
        - derived class virtual method are get added to 1st parent vtable's
            - class CC:class CA, class CB
                - class CC's virtual methods are get added to CA's vtable that is at vptr[0];
- dynamic cast
- interface class
    - class having only pure virtual functions.
- Abstract class
    - class having other methods with some pure virtual functions.
- Template pattern
    - maintain business flow in base class and delaying or deffering.
*/

namespace basic_virtual01 {
class CA {
public:
    void fun1() {
        cout <<"CA fun1" << endl;
    }
    virtual void fun2() {
        cout <<"CA fun2" << endl;
    }
    virtual void fun3() {
        cout <<"CA fun3" << endl;
    }
};

int main1() {
    cout << "sizeof(CA):: " << sizeof(CA)<<endl;    // it should be value of pointer size:: that to vary depending upon compiler
    CA obj;
    //obj.fun2();
    //((void (*)())*(long*)*(long *)&obj)();

    // step 1 reach vptr
    long *vptr = (long *)&obj;

    // step 2 reach vtable
    long *vtable = (long *)*vptr;

    // step 3 reach function
    typedef void (*FPTR)();
    FPTR fp = (FPTR)vtable[0];

    // step 4 callback
    fp();

    fp = (FPTR)vtable[1];
    fp();
}

int main () {
    CA obj;
    CA &objRef = obj;
    CA *ptr = &obj;

    obj.fun1();     // directly resolved from code seg
    objRef.fun1();  // directly resolved from code seg
    ptr->fun1();    // directly resolved from code seg

    obj.fun2();     // directly resolved from code seg
    objRef.fun2();  // resolved via vtable
    ptr->fun2();    // resolved via vtable
}
}

namespace basics_vitual02 {
class CA {
public:
    void fun1() {
        cout <<"CA fun1" << endl;
    }
    virtual void fun2() {
        cout <<"\tCA fun2" << endl;
    }
    virtual void fun3() {
        cout <<"\tCA fun3" << endl;
    }
};

class CB: public CA {

};

int main () {
    CA obj1;
    CB obj2;

    long *ptr1 = (long *)&obj1;
    long *vtable1 = (long *)*ptr1;
    cout << "CA:: Vtable:: " << vtable1 << endl;
    for (size_t i = 0x00; i<2;i++) {
        ((void (*)())vtable1[i])();
    }

    long *ptr2 = (long *)&obj2;
    long *vtable2 = (long *)*ptr2;
    cout << "CB:: Vtable:: " << vtable2 << endl;
    for (size_t i = 0x00; i<2;i++) {
        ((void (*)())vtable2[i])(); // copies base class vtable to derived class
    }
}
}

namespace basics_vitual03 {

class CA {
public:
    void fun() {
        cout <<"CA fun" << endl;
    }

    virtual void fun1() {
        cout <<"\tCA fun1" << endl;
    }
    virtual void fun2() {
        cout <<"\tCA fun2" << endl;
    }
    virtual void fun3() {
        cout <<"\tCA fun3" << endl;
    }
};

class CB: public CA {
public:
    virtual void fun4()         // uppending
    {
        cout <<"\tCB fun4 uppending" << endl;
    }
    /*
    void fun3()     // hidding
    {
        cout <<"\tCB fun3 hidding" << endl;
    }
    */
    virtual void fun3(int ) // on overloading base virtual method in derived class that method get upppended in vtable of derived class
    {
        cout <<"\tCB fun3 uppending" << endl;
    }
    //virtual void fun1(int) override   // gives compiler error
    virtual void fun1() override
    {
        cout <<"\tCB fun1 overriding" << endl;
    }

};

int main () {
    CA obj1;
    CB obj2;

    long *ptr1 = (long *)&obj1;
    long *vtable1 = (long *)*ptr1;
    cout << "CA:: Vtable:: " << vtable1 << endl;
    for (size_t i = 0x00; i<3;i++) {
        ((void (*)())vtable1[i])();
    }

    long *ptr2 = (long *)&obj2;
    long *vtable2 = (long *)*ptr2;
    cout << "CB:: Vtable:: " << vtable2 << endl;
    for (size_t i = 0x00; i<5;i++) {
        ((void (*)())vtable2[i])(); // copies base class vtable to derived class
    }
}
}

namespace basics_vitual04 {
class CA {
public:
    CA()
    /*
        - setvptr:: CA::vtable
    */
    {
    }
    void fun() {
        cout <<"CA fun" << endl;
    }
    virtual void fun1() {
        cout <<"\tCA fun1" << endl;
    }
    virtual void fun2() {
        cout <<"\tCA fun2" << endl;
    }
    virtual void fun3() {
        cout <<"\tCA fun3" << endl;
    }
};

class CAT {
public:
    CAT () {
    }
};

class CB: public CA {
    CAT cat;
public:
    CB()
    /*
        - call base class ctor:: CA::CA()
        - setvptr:: CB::vtable
        - call container ctor:: CAT::CAT()
    */
    {
    }

    virtual void fun1() override
    {
        cout <<"\tCB fun1 overriding" << endl;
    }
};

int main () {
    CB obj1;

    CA *ptr = &obj1;
    ptr->fun1();    // vptr = CB::vtable
    //ptr->CA::CA();    //updating vptr to CA::vtable
    ptr->fun1();    // vptr = CB::vtable

}
}

namespace multi_inheritance {
class CA {
public:
    virtual void CaFun1() {
        cout << "\tCA:: Fun1" << endl;
    }
    virtual void CaFun2() {
        cout << "\tCA:: Fun2" << endl;
    }
};

class CB {
public:
    virtual void CbFun1() {
        cout << "\tCB:: Fun1" << endl;
    }
    virtual void CbFun2() {
        cout << "\tCB:: Fun2" << endl;
    }
};

class CC: public CA, public CB
{
public:
    virtual void CcFun1() {
        cout << "\tCC:: Fun1" << endl;
    }
    virtual void CcFun2() {
        cout << "\tCC:: Fun2" << endl;
    }
};

void PrintDetails(string str, void *obj, int count) {
    long *vptr = (long *)obj;
    long *vtable = (long *) *vptr;
    cout << str << vtable << endl;
    for (size_t i =0; i <count;i++) {
        ((void (*)())vtable[i])();
    }
    cout << "-----------------------------" << endl;
}

int main1 () {
    CA ca_obj;
    CB cb_obj;
    CC cc_obj;

    PrintDetails("CA::vtable:: ", &ca_obj,2);
    PrintDetails("CB::vtable:: ", &cb_obj,2);
    PrintDetails("CC::CA::vtable:: ", &cc_obj,4);       // vptr 1 contains CA's and CC's v entries:: 2+2
    PrintDetails("CC::CA::vtable:: ", ((long*)&cc_obj)+1,2);    // moving to CB's vptr

    /*
    cout << "CC size:: " << sizeof(CC)<< endl;
    cout << "-----------------------------" << endl;

    long *vptr = (long *)&obj;
    long *vtable = (long *) *vptr;

    cout << "CC::CA::vtable[0] "<< vtable<< endl;
    for (size_t i =0; i <4;i++) {
        ((void (*)())vtable[i])();  // function uppending to 1st parent vtable
    }
    cout << "-----------------------------" << endl;


    long *vtable1 = (long *) vptr[1];
    cout << "CC::CB::vtable[1] "<< vtable1<< endl;
    for (size_t i =0; i <2;i++) {
        ((void (*)())vtable1[i])();
    }
    cout << "-----------------------------" << endl;
    */

    cout << "-----------------------------" << endl;
    CB *ptr = &cc_obj;
    ptr->CbFun1();
    //ptr->CcFun1();    // error CB dont have CcFun1()
}

int main() {
    CA *obj = new CC();
    obj->CaFun1();  // CA::vtable[0]
    obj->CaFun2();  // CA::vtable[1]
    cout << "-----------------------------" << endl;

    CB *obj1 = (CB *)obj;
    obj1->CbFun1(); // CA::vtable[0]
    obj1->CbFun2(); // CA::vtable[1]
    cout << "-----------------------------" << endl;
    obj1++;
    obj1->CbFun1(); // CB::vtable[0]
    obj1->CbFun2(); // CB::vtable[1]
    cout << "-----------------------------" << endl;

    CB *obj2 = (CC *)obj; // downcast
    obj2->CbFun1(); // CA::vtable[0]
    obj2->CbFun2(); // CA::vtable[1]
    cout << "-----------------------------" << endl;

    CB *obj3 = dynamic_cast<CB*>(obj); // downcast
    obj3->CbFun1(); // CA::vtable[0]
    obj3->CbFun2(); // CA::vtable[1]
    cout << "-----------------------------" << endl;
}
}

namespace basic_virtual02 {
class CA {
public:
    CA () {
        fun();
    }
    void MyFun() {
        fun();
    }
    ~CA() {
        fun();
    }
    virtual void fun () {
        cout << "apple" << endl;
    }
};

class CB:public CA {
public:
    CB () {
        fun();
    }
    ~CB() {
        fun();
    }
    virtual void fun () {
        cout << "orange" << endl;
    }
};

int main () {
    CB obj;
    obj.MyFun();
}
}


class Bank {
public:
};

int main () {
}


