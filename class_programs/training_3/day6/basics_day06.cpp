#include <iostream>
#include <string>
#include <stdlib.h>
#include <map>
#include <typeinfo>
using namespace std;
/*
- exception handling
    - its handshake between vendor and consumer.
    - set_terminate(void (*fun)()):: used to override terminate method
        - this should be registered before exception generation, else it wont call Myterminate method.
    - exception or try-catch flow
        - copy exception info into catch table.
            - catch table per try.
        - release local variables.
        - copy into of exception into catch block and execute catch block.
            - per try there may be number of catch blocks.
            - after catch table executed catch table get die.
    - general exception
    - rethrow:: catch table information rethrown
    - always catch with reference.
    - exception should not overlap:: scenario like throwing exception in Dtor.
        - Never throw exceptions from Dtor.
    - gracefully throw exceptions from Ctor to avoid memory leak.
    - internal operations on new operator
        CAT *temp = operator new(){return addr}; // new operator exceptions are handled by inner try block.
        try {
            temp->CAT::CAT();
        }
        catch (...){
            free(temp);
            throw;
        }
        objPtr = temp;
- closure/functors
    - carry the parent context to callback
    - implemented using functors
        - functors contains refernce of local objects.
- Inheritance
    - lsp:: liskov's substitution principle
        - base class hold's pointer or refernce of derived class object;
        - object slicing: only visible sliced info that is base class info only.
    - vertical access control:: change access specifier of member (excluding private member) of base class in derived class.
        - using base_class::member
            - using CA::idata;
    - function/ mehtods in derived class
        - hidding
        - overload
- GRASP/ SOLID
    - yagni
    - Kiss
    - low coupling
    - high cohesion
    - pure fabrication
    - SRP
    - OCP
    - LOD
    - LSP
    - cyclomatic complexcity
    - null object
    - value object
    - RTTI
    - controlling
    - creator
    - DIP (IOC)
    - protected variation.
*/
namespace exception_handling {
class CA {
    int _x;
    static int _y;
public:
    CA(){
        _x=++_y;
        cout << "CA Ctor" <<endl;
    }
    CA(const CA &ObjRef ){
        _x=++_y;
        cout << "CA Copy Ctor" <<endl;
    }
    ~CA(){
        cout << "CA Dtor x = "<< _x <<endl;
    }
};

void VendorFun(int para) {
    cout << "Vendor api called" << endl;
    if (para == 100) {
        throw 10;
    }
    cout << "Vendor api returned" << endl;
}

void MyTerminate ()
{
    cout << "Resource De-allocated in MyTerminate !!!!!!!!" << endl;
    exit(0);
}

int CA::_y=0;

int main1 () {
    cout << "Resource Allocated !!!!!!!!" << endl;
    set_terminate(MyTerminate); // always set before exeption generation.
    try {
        CA obj;
        throw obj;
        VendorFun(100);
    }
    catch (int exp) {
        if (exp == 10) {
            cout << "resource already registered" << endl;
        }
    }
    catch (CA obj){
        cout << "CA exp cought"<< endl;
    }// local objects destroyed 1st then catch table

    cout << "Resource De-allocated in main !!!!!!!!" << endl;
    return 0;
}

int main2 () {

    try {
        //throw 100;    //int
        //throw 100.3;    //double
        throw 100.2f;   //general
    }
    catch (int exp) {
        cout << "exp int " << endl;
    }
    catch (double exp) {
        cout << "exp double " << endl;
    }
    catch (...) // general exception
    {
        cout << "general exp " << endl;
    }
    return 0;
}

int main3 () {
    try {
        try {
            throw 100.3;
        }
        catch (int exp) {
            cout << "exp (outside) int "<< exp << endl;
        }
        cout << "orange" << endl;
    }
    catch (int exp) {
        cout << "exp (outside) int " << endl;
    }
    catch (double exp) {
        cout << "exp double " << endl;
    }
    catch (...) // general exception
    {
        cout << "general exp " << endl;
    }
    return 0;
}

int main4 () {
    try {
        try {
            throw 100;
        }
        catch (int exp) {
            cout << "exp (outside) int "<< exp << endl;
            throw 300;  // replace
        }
        cout << "orange" << endl;
    }
    catch (int exp) {
        cout << "exp (inside) int "<< exp << endl;
    }
    catch (double exp) {
        cout << "exp double " << endl;
    }
    catch (...) // general exception
    {
        cout << "general exp " << endl;
    }
    return 0;
}

int main5 () {
    try {
        try {
            throw 100;
        }
        catch (int exp) {
            exp = 99;
            cout << "exp (outside) int "<< exp << endl;
            throw;  // rethrow:: catch table information rethrown
        }
        cout << "orange" << endl;
    }
    catch (int exp) {
        cout << "exp (inside) int "<< exp << endl;
    }
    catch (double exp) {
        cout << "exp double " << endl;
    }
    catch (...) {
        cout << "general exp " << endl;
    }
    return 0;
}

int main6 () {
    try {
        try {
            throw 100;
        }
        catch (int &exp) {  //catched by reference
            exp = 99;   // catch table contents will be reflected.
            cout << "exp (outside) int "<< exp << endl;
            throw;  // rethrow:: catch table information rethrown
        }
        cout << "orange" << endl;
    }
    catch (int exp) {
        cout << "exp (inside) int "<< exp << endl;
    }
    catch (double exp) {
        cout << "exp double " << endl;
    }
    catch (...) {
        cout << "general exp " << endl;
    }
    return 0;
}

class CB {
public:
    CB(){
        cout << "CB Ctor" <<endl;
    }
    ~CB(){
        cout << "CB Dtor "<<endl;
        throw 10;   // exception overlapping not allowed
    }
};

int main7 (){
    try {
        try {
            CB obj;
            throw 100;
        }
        catch (int exp) {
            cout << "int (outer) exp:: "<< exp << endl;
        }
    }
    catch (int exp) {
        cout << "int (inner) exp:: "<< exp << endl;
    }
    return 0;
}

class CAT {
public:
    CAT() {
        cout << "CAT Ctor" <<endl;
        throw 10;
    }
    ~CAT(){
        cout << "CAT Dtor "<<endl;
    }
};

int main () {
    CAT *objPtr= NULL;
    try {   // inner try block
        objPtr = new CAT();
        /*
            // internal operations on new operator
            CAT *temp = operator new(){return addr}; // new operator exceptions are handled by inner try block.
            try {
                temp->CAT::CAT();
            }
            catch (...){
                free(temp);
                throw;
            }
            objPtr = temp;
        */
    }
    catch (int exp) {
        cout << "exp int :: " << exp <<endl;
    }
    if (objPtr == NULL) {
        cout << "objPtr:: NULL" << endl;
    }
    else {
        cout << "objPtr:: NOt NULL" << endl;
        delete objPtr;
    }
    return 0;
}
}

namespace basics_functors {
template<typename T>
void VendorFun(T fp) {
    cout << "vendor started" << endl;
    fp();
    cout << "vendor completed" << endl;
}

void ClientFun () {
    cout << "client fun called" << endl;
}

int main1 () {
    VendorFun(ClientFun);   // depending upon parameter compiler detects
    //VendorFun<void(*)()>(ClientFun);
    return 0;
}

class MyFunctor {
    int &_ii;
    string &_kk;
    double &_pii;
public:
    MyFunctor(int &ii, string &kk, double &pii): _ii(ii), _kk(kk), _pii(pii) {}
    void operator()() {
        cout << "i:: " << _ii << " k:: " << _kk << " pi:: " << _pii << endl;
    }
};

int main () {
    int i = 100;
    string k ="sample";
    double pi = 3.14;
    MyFunctor obj(i, k, pi);
    VendorFun(obj);
    return 0;
}
}

namespace basic_inheritance01 {
class Animal {
private:
    int _x;
protected:
    int _y;
public:
    int _z;
    Animal (int x, int y, int z): _x(x), _y(y), _z(z) {
        cout << "Animal Param Ctor" << endl;
    }
    Animal (): _x(0), _y(0), _z(0) {
        cout << "Animal Default Ctor" << endl;
    }
    void AnimalDisplay() {
        cout << "x = " << _x << endl;
        cout << "y = " << _y << endl;
        cout << "z = " << _z << endl;
        cout << "------------------------------" << endl;
    }
    virtual ~Animal() {
        cout << "Animal Dtor" << endl;
    }
};

class Cat: public Animal {
public:
    Cat (){
        cout << "Cat Default Ctor" << endl;
    }
    void CatDisplay() {
        cout << "y = " << _y << endl;
        cout << "z = " << _z << endl;
        cout << "------------------------------" << endl;
    }
    ~Cat() {
        cout << "Cat Dtor" << endl;
    }//Animal::~Animal()
};

int main () {
    //Cat cobj;
    Animal *lsp_ptr = new Cat(); //lsp


    delete lsp_ptr; //called by pointer type so Animal Dtor gets called:: to get call derived class make base Dtor virtual
    return 0;
}
}

namespace basic_inheritance02 {
class CA {
private:
    int _x;
protected:
    int _y;
public:
    int _z;
    CA (): _x(0), _y(0), _z(0) {
        cout << "CA Default Ctor" << endl;
    }
    void DisplayCA() {
        cout << "CA display" << endl;
        cout << "x = " << _x << endl;
        cout << "y = " << _y << endl;
        cout << "z = " << _z << endl;
        cout << "------------------------------" << endl;
    }
};
class CB: protected CA {
public:
    using CA::_z;
    //using CA::_x;   // error cant change private member access
    void DisplayCB() {
        cout << "CB display" << endl;
        //cout << "x = " << _x << endl; //x is private of base
        cout << "y = " << _y << endl;
        cout << "z = " << _z << endl;
        cout << "------------------------------" << endl;
    }
};
class CC: public CB {
public:
    void DisplayCC() {
        cout << "CC display" << endl;
        //cout << "x = " << _x << endl; //x is private of base
        cout << "y = " << _y << endl;
        cout << "z = " << _z << endl;
        cout << "------------------------------" << endl;
    }
};

int main (){
    CA obj;
}
}


class CA {
public:
    void fun1() {
        cout << "CA fun1 called" << endl;
    }
    void fun2() {
        cout << "CA fun2 called" << endl;
    }
};

class CB: public CA {
public:
    void fun2() // hidding
    {
        cout << "CB fun2 called" << endl;
    }
    void fun3() {
        cout << "CB fun3 called" << endl;
    }
};
int main1 (){
    CB b_obj;
    b_obj.fun1();
    b_obj.fun2();
    b_obj.fun3();

    CA &a_objref = b_obj;
    a_objref.fun1();
    a_objref.fun2();
    //a_objref.fun3();  // dont have access bcz object slicing
}

class Math {
public:
    void AddFun(int x){
        cout << "AddFun Math 1 para" << endl;
    }
    void AddFun(int x, int y){
        cout << "AddFun Math 2 para" << endl;
    }
};

class MathEx: public Math{
public:
    using Math::AddFun; // expose base method to user overload base method
    void AddFun(int x, int y, int z){
        cout << "AddFun MathEx 3 para" << endl;
    }
};

MathEx math;

int main () {
    MathEx math;
    math.AddFun(1);
    math.AddFun(1,1);
    math.AddFun(1,1,1);
    ::math.AddFun(2,2,3);
}
