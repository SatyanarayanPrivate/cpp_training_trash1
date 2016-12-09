#include <iostream>
#include <string.h>
using namespace std;
/*
- Object:
    - identity
    - state
    - behaviour
        - inspector: methods which not change state of object.
            - if you suffix function with "const" keyword then it behaves has inspector
            - inspector can call only inspector methos of same class.
        - mutator: methods which change state of object.
        - nullipotent: code which does not alter the state of target object (database or else).
        - idempotent: code which alter the state of target object (database or else).

- transpilers:
    convert one source to other, like c++ to c and compile.
- Object Location:
    - stack
    - heap
    - data
    - register
    - TLS: thread location storage

- cppcheck:: tools to detect using uninitialized variable
- Stack frame: every function have its own stack frame.
- param pushed on stack from right to left:: fun(int a, int b) b pushed 1st then a.

- object
- class
- this
- inspector
- mutator
- const: for const object, only inspector gets called. and all member of obj become const except static member bcz static member is not part of object.
- mutable: member never const even in inspector and const object.
- Ctor
    - default Ctor
    - parameterized Ctor
    - initialization list
    - explicit Ctor:: allow only for ctor syntax that is not {};
- const member
- encapsulation:
    - having data and method together
    - hide data and expose methods
- Abstract
    - hiding complexcity
- Dtor
- static member
    - for static variable data is allocated before main gets called, static variable may be from func, global or class.
- static const
- enum
    - scoped enum vs non scoped enum.
*/
namespace basics01 {
class MyClass {
public:
        int x = 10; //c++11
        int y = 20;
        int z = 30;

        void Display () const   // acts as inspector
        {

            //SetValues (10);     // Compiler error:: inspector can call to only other inspector

            int k = 200;    // local objects state can be changed.
            k += 100;

            cout << "x = " << x << endl;    // while acccessing state of class, compiler uses offset calculation.:: x=>offset[0]
            cout << "y = " << y << endl;    // y=>offset[4]
            cout << "z = " << this->z << endl;  // compiler uses explicitly this pointer
            cout << "---------------------------------------------" << endl;
        }

        void SetValues (int val) {
            x = val;
            y = val;
            z = val;
        }
};


int main1 (void) {

    MyClass obj;
    obj.x = 101;
    obj.SetValues(900);
    obj.Display ();

    MyClass obj1;
    obj1.y = 201;
    obj1.SetValues(901);
    obj1.Display ();

    return 0;
}

int main (void) {

    MyClass obj;
    obj.x = 102;
    obj.SetValues(103);
    obj.Display();

    const MyClass obj1; // for const object only inspector gets called.
    //obj1.x = 102;
    //obj1.SetValues(103);
    obj1.Display();

    return 0;
}
}

namespace basics02 {
class Employee
{
public:
    int Eid;
    string Ename;
    mutable int Esalary;

    Employee (): Eid(0x00), Ename("no name"), Esalary(0x00)
    {
        cout << "Default Ctor" << endl;
    }
    explicit Employee (int Eid, string Ename, int Esalary): Eid(Eid), Ename(Ename), Esalary(Esalary)
    {
        cout << "Parameterized Ctor" << endl;
    }

    void SetEmplyoeeDetails(int eid, string ename, int esalary)
    {
        Eid = eid;
        Ename = ename;
        Esalary = esalary;
    }

    void Display(int increament = 0) const
    {

        Esalary += increament;
        cout << "Eid= " << Eid << endl;
        cout << "Ename= " << Ename << endl;
        cout << "Esalary= " << Esalary << endl;
        cout << "====================================================" << endl;
    }
};


int main (){
    const Employee sachin;
    //sachin.SetEmplyoeeDetails(1, "sachin", 100);  // as method mutators
    sachin.Esalary += 500;
    sachin.Display();

    Employee sachin1;
    sachin1.SetEmplyoeeDetails(2, "sachin1", 200);
    sachin1.Display(1200);

    Employee sachin3(3, "sachin3", 1234);
    sachin3.Display();

    //Employee sachin4 = {4, "sachin4", 123};    //c++11 for explicit this wont work
    //sachin4.Display();

    return 0;
}
}

namespace basic03 {
class Employee
{
private:
    const int Eid;
    string Ename;
    mutable int Esalary;

public:
    Employee (): Eid(10), Ename("no name"), Esalary(0x00)
    {
        cout << "Employee Default Ctor Allocate resources (RAII) " << endl;
    }
    Employee (int Eid, string Ename, int Esalary): Eid(Eid), Ename(Ename), Esalary(Esalary)
    {
        cout << "Employee Parameterized Ctor Allocate resources (RAII)" << endl;
    }

    ~Employee () {
        cout << "Employee Dtor releasing resources " << endl;
    }

    void SetEmplyoeeDetails(string ename, int esalary)
    {
        Ename = ename;
        Esalary = esalary;
    }

    void Display(int increament = 0) const
    {

        Esalary += increament;
        cout << "Eid= " << Eid << endl;
        cout << "Ename= " << Ename << endl;
        cout << "Esalary= " << Esalary << endl;
        cout << "====================================================" << endl;
    }
};


int main () {

    Employee sachin (101,"sachin", 100);
    sachin.Display();

    return 0;
}
}

namespace basic04 {
class CA
{
    int x;
public:
    static int s;
    static const int sc;

    CA ():x(++s)
    {
        cout << "Default Ctor x= " << x << endl;
    }

    void ListMembers () const
    {
        cout << "x = " << x << endl;
        cout << "sc = " << sc << endl;
        cout << "s = " << s << endl;
    }
    static void StatFun () {
        cout << "Static func" << endl;
        cout << "sc = " << sc << endl;
        cout << "s = " << s << endl;
    }
    ~CA ()
    {
        cout << "Dtor x = "<< x << endl;
    }
};

int CA::s;
const int CA::sc = 10;
void fun () {
    CA obj;
    CA obj1;
    CA obj2;
}

int main1 () {
    fun ();
    CA obj;
    CA obj1;
    CA obj2;

    return 0;
}

int main () {
    const CA obj;
    obj.s = 100;    // static member is not part of object.
    obj.ListMembers();
    CA::s = 101;
    obj.StatFun();
    CA::StatFun();

    return 0;
}
}

namespace basic05 {
#define fun1() {cout << "fun1 called"<<endl;}

inline void fun2() {
    cout << "fun2 called" << endl;
}
void fun3() {
    cout << "fun3 called" << endl;
}

class CA {
public:
    void fun4() {cout << "fun4 called:"<< endl;}    // default inline
    void fun5();
    void fun6();
};
inline void CA:: fun5() {cout << "fun5 called:"<< endl;}    // we declaire as inline else work as normal function
void CA:: fun6() {cout << "fun6 called:"<< endl;}


int main ()
{
    fun1(); // resoleved at preprossing stage
    fun2(); // resolved at compile stage
    fun3(); // resolved at linker stage

    return 0;
}
}
namespace assignment01 {
enum class DlrRu
{
    INR,
    USD
};

class USD2INR
{
    double usd;
    double inr;
public:
    USD2INR (): usd(1.0), inr(67.0)
    {
    }
    double GetRate(DlrRu choice) {
        switch (choice) {
            case DlrRu::INR: return inr;
            case DlrRu::USD: return usd;
            default:
                return 0.0;
        }
    }
};

enum class PndRu
{
    INR,
    PND
};

class PND2INR
{
    double pnd;
    double inr;
public:
    PND2INR():  pnd(1.0), inr(85.0)
    {
    }
    double GetRate(PndRu choice) {
        switch (choice) {
            case PndRu::INR: return inr;
            case PndRu::PND: return pnd;
            default:
                return 0.0;
        }
    }
};

enum class PndDlr {
    USD,
    PND
};

class PND2USD
{
    USD2INR usd2inr;
    PND2INR pnd2inr;
    double usd;
public:
    PND2USD (double pnd)
    {
        double inr = pnd2inr.GetRate(PndRu::INR) * pnd;
        usd = inr / usd2inr.GetRate(DlrRu::INR);
    }
    double GetUsd () {
        return usd;
    }

    double GetRate(PndDlr ch) {
        switch (ch) {
            case PndDlr::PND : return ;
        }
    }
};

class USD2PND
{
    USD2INR usd2inr;
    PND2INR pnd2inr;
    double pnd;
public:
    USD2PND (double usd)
    {
        double inr = usd2inr.GetRate(DlrRu::INR) * usd;
        pnd = inr / pnd2inr.GetRate(PndRu::INR);
    }
    double GetPnd () {
        return pnd;
    }
};


int main (){
    PND2USD obj1 (1);
    cout << "PND2USD(1) = " << obj1.GetUsd() << endl;

    USD2PND obj2 (1);
    cout << "USD2PND(1) = " << obj2.GetPnd() << endl;

    return 0;
}
}

// problem on flipkart and amazon on bidding

enum class AmazonItems 
{   
    
};

int main () {
    return 0;
}
