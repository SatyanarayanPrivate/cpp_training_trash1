#include <iostream>
#include <string>
#include <math.h>
using namespace std;
/*
- operator overloading
    -
    - parameter
    - casting operators
- functors
- friend functions
    -  grand permission to private variable through object.
    - friend function does not belongs to class.
- initializer_list
*/

namespace operator_overloading {
class PolarCord;

class RectCord
{
    double _xCord;  // general conventions that private variable starts with "_"
    double _yCord;
public:
    RectCord (): _xCord (0.0), _yCord(0.0)
    {
    }
    RectCord (double x, double y): _xCord (x), _yCord(y)
    {
    }

    string operator()()
    {
        string str = "(";
        str += to_string (_xCord);
        str += " , ";
        str += to_string (_yCord);
        str += ")";
        return str;
    }

    RectCord operator+(RectCord &ObjRef)
    {
        /*
        //RectCord temp (this->_xCord, this->_yCord);
        //return temp;
        RectCord temp1;
        temp1._xCord = 2.3; // we can access private members to in local method
        temp1._yCord = 2.3;
        */
        return RectCord (this->_xCord + ObjRef._xCord, this->_yCord + ObjRef._yCord);
    }

    operator PolarCord();
};

class PolarCord
{
    double _angle;
    double _distace;
public:
    PolarCord ():_angle (0.0), _distace (0.0)
    {
    }
    PolarCord (double angle, double distace): _angle (angle), _distace(distace)
    {
    }
    void Display()
    {
        cout << "(" << _angle << " , " << _distace << ")" << endl;
    }

    operator RectCord()
    {
        // do calculations

        return RectCord (2.222, 4.4444);
    }
    operator int ()
    {
        // conversion
        return 777;
    }
};

RectCord::operator PolarCord()
{
    // do conversion of Rect to polar
    double angle = atan(_yCord/_xCord);
    double dist = sqrt((_xCord*_xCord) + (_yCord *_yCord));
    return PolarCord (angle, dist);
}

int main1 ()
{
    RectCord robj1 (2.3,4.5);
    RectCord robj2 (1.3,4.3);

    cout << robj1.operator()() << endl;
    cout << robj2.operator()() << endl;
    cout << "--------------------------------------" << endl;

    RectCord radd = robj1.operator+(robj2);
    cout << radd.operator()() << endl;
    cout << "--------------------------------------" << endl;

    PolarCord pobj1 = robj1.operator PolarCord();
    pobj1.Display();
    cout << "--------------------------------------" << endl;

    robj1 = pobj1.operator RectCord();
    cout << robj1.operator()() << endl;
    cout << "--------------------------------------" << endl;

    int val = pobj1.operator int();

    cout << "int = " << val << endl;
    return 0;
}

int main ()
{
    RectCord robj1 (2.3,4.5);
    RectCord robj2 (1.3,4.3);

    cout << robj1() << endl;
    cout << robj2() << endl;
    cout << "--------------------------------------" << endl;

    RectCord radd = robj1 + (robj2);
    cout << radd() << endl;
    cout << "--------------------------------------" << endl;

    PolarCord pobj1 = robj1;
    pobj1.Display();
    cout << "--------------------------------------" << endl;

    robj1 = pobj1;
    //double val1 = pobj1.operator double();
    //robj1 = pobj1.operator RectCord();
    cout << robj1() << endl;
    cout << "--------------------------------------" << endl;

    int val = pobj1;
    cout << "int = " << val << endl;
    return 0;
}
}

namespace friend_function {
class CComplex
{
    double _real;
    double _imaginary;
public:
    CComplex (): _real(0.0),_imaginary(0.0)
    {
    }
    CComplex (double real, double imaginary): _real(real),_imaginary(imaginary)
    {
    }

    CComplex operator+ (const CComplex &ObjRef)
    {
        return CComplex (_real+ObjRef._real, _imaginary+ObjRef._imaginary);
    }
    CComplex operator+ (const int val)
    {
        this->_imaginary = this->_imaginary + val;
        return *this;
    }
    friend CComplex & operator+ (const int val, CComplex &ObjRef)
    {
        ObjRef._real = ObjRef._real + val;
        return ObjRef;
    }

    operator int ()
    {
        return this->_imaginary + this->_real;
    }
    ostream & operator<<(ostream & os)
    {
        os << this->_real << (this->_imaginary >= 0.0 ? " + " : "") << this->_imaginary << "i" << endl;
        return os;
    }

    friend ostream & operator<<(ostream & os, const CComplex &obj)
    {
        os << obj._real << (obj._imaginary >= 0.0 ? " + " : "") << obj._imaginary << "i" << endl;
        return os;
    }
};


int main ()
{
    CComplex obj1 (10.3, -12.3);
    obj1 << cout << endl;   // ostream & operator<<(ostream & os)
    cout << obj1 << endl;   // friend ostream & operator<<(ostream & os, CComplex &obj)

    CComplex obj2 (101.3, 121.3);
    cout << obj2 << endl;
    CComplex obj3 = obj1 + obj2;
    cout << obj3 << endl;
    obj3 = obj1 + 10;
    cout << obj3 << endl;
    obj3 = 10 + obj1;
    cout << obj3 << endl;

    int mag = obj1;
    cout << "magnitude = " << mag << endl;
    return 0;
}
}

#if 0
namespace problem_03 {
//pnd, euro, dollar
//R = P + E + D
/*
Rs = P + E + D
P + D + E
D + P + E
D + E + P
E + P + D
E + D + P
*/


class Pound
{
    double inr;
    double pnd;
public:
    Pound (double pnd): inr(80), pnd(pnd)
    {
    }
    Pound operator+(Pound & ObjRef)
    {

    }
    Pound operator+(Euro & ObjRef)
    {
        rs = ObjRef;
    }
    Pound operator+(Dollar & ObjRef)
    {

    }

    operator Rs()
    {
        return inr*pnd;
    }
};


int main ()
{
    returno
}
}
#endif
namespace problem_04 {
#define ARR_LEN 5
class CArray
{
    int _Arr[ARR_LEN];
public:
    CArray ()
    {
        cout << "Default Ctor" << endl;
        for (size_t i = 0x00; i < ARR_LEN; i++)
        {
            _Arr[i] = i;
        }
    }
    CArray (int a, int b, int c, int d, int e): _Arr{a,b,c,d,e}
    {
        cout << "Param Ctor" << endl;
    }

    CArray (initializer_list <int> list)    // pririty for initializer_list in between param ctor
    {
        cout << "initializer list Ctor" << endl;
        initializer_list <int>::iterator its= list.begin();
        initializer_list <int>::iterator ite= list.end();
        //for (size_t i = 0x00; its != ite; its++)
        for (size_t i = 0x00; i < (list.size()); its++, i++)
        {
            _Arr[i] = *its;
        }
    }
    int & operator[] (int index)
    {
        return _Arr[index];
    }

    friend ostream &operator<<(ostream &os, const CArray &par)
    {
        cout << "Array:: ";
        for (size_t i = 0x00; i < ARR_LEN; i++)
        {
            cout << par._Arr[i] << " ";
        }
        cout << endl;
        return os;
    }

};

int main ()
{
    CArray objArr = {11,22,33,44,55};
    objArr[2] = 999;
    int val = objArr[1];
    objArr[3] = objArr[2];

    cout << objArr << endl;
    cout << "val = " << val <<endl;
    return 0;
}
}

namespace cppcheck {
//cppcheck
class Employee
{
    int _eid;
    string _ename;
    double _esalary;
public:
    Employee(int eid,string ename,double salary): _eid(eid), _ename(ename),_esalary(salary)
    {
    }

    void Display ()
    {
        cout << "Eid = " << _eid << endl;
        cout << "EName = " << _ename<< endl;
        cout << "Eid = " << _esalary<< endl;
        cout << "---------------------------"<<endl;
    }
};

int main()
{
    Employee *p = new Employee(100,"sachin", 1000.00);;
    Employee *p1 = new Employee(101,"sachin1", 1001.00);

    p->Display();
    p1->Display();

    delete p;

    return 0;
}
}

//lazyload
#define ARR_LEN 5
class SmartArray
{
    int _Arr[5];
public:
    SmartArray (initializer_list <int> list)    // pririty for initializer_list in between param ctor
    {
        cout << "initializer list Ctor" << endl;
        initializer_list <int>::iterator its= list.begin();
        initializer_list <int>::iterator ite= list.end();
        //for (size_t i = 0x00; its != ite; its++)
        for (size_t i = 0x00; i < (list.size()); its++, i++)
        {
            _Arr[i] = *its;
        }
    }

    class Helper
    {
        SmartArray *outptr;
        int index;
    public:
        Helper(SmartArray *outptr, int index): outptr(outptr), index(index) {}

        Helper & operator=(int val)
        {
            cout << "writing ...." << endl;
            this->outptr->_Arr[index]  = val;
            return *this;
        }
        operator int()
        {
            cout << "reading ...." << endl;
            return this->outptr->_Arr[index];
        }
        Helper &operator= (Helper ObjRef)   // if this not defined then compiler uses default operator= which is bitwise copy
        {
            cout << "writing/reading ...." << endl;
            this->outptr->_Arr[index] = ObjRef.outptr->_Arr[index];
            return *this;
        }
    };

    Helper operator[](int index)
    {
        return Helper(this, index);
    }

    friend ostream &operator<<(ostream &os, const SmartArray &par)
    {
        cout << "Array:: ";
        for (size_t i = 0x00; i < ARR_LEN; i++)
        {
            cout << par._Arr[i] << " ";
        }
        cout << endl;
        return os;
    }
};

int main ()
{
    SmartArray objArr = {11,22,33,44,55};
    objArr[2] = 999;        //writing
    int val = objArr[1];    //reading
    objArr[3] = objArr[2];  // read/write
    cout << objArr << endl;

    return 0;
}

