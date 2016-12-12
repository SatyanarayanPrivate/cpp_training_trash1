#include <iostream>
#include <string>
#include <map>
using namespace std;

#define ARR_LEN 2
#if 0
class SmartArray
{
    int _Arr[ARR_LEN][ARR_LEN];
public:
    SmartArray ()
    {
        int count = 0x00;
        for (size_t i = 0x00; i < ARR_LEN; i++) {
            for (size_t j = 0x00; j < ARR_LEN; j++)
            {
                _Arr[i][j] = count++;
            }
        }
    }
    class Helper
    {
        SmartArray *outptr;
        int _RIndex;
        int _CIndex;
    public:
        Helper(SmartArray *outptr, int Rindex, int Cindex=0): outptr(outptr), _RIndex(Rindex), _CIndex(Cindex) {}

        Helper & operator=(int val)
        {
            cout << "writing ...." << endl;
            this->outptr->_Arr[_RIndex][_CIndex]  = val;
            return *this;
        }
        operator int()
        {
            cout << "reading ...." << endl;
            return this->outptr->_Arr[_RIndex][_CIndex];
        }
        Helper &operator= (Helper &ObjRef)   // if this not defined then compiler uses default operator= which is bitwise copy
        {
            cout << "writing/reading ...." << endl;
            this->outptr->_Arr[_RIndex][_CIndex] = ObjRef.outptr->_Arr[_RIndex][_CIndex];
            return *this;
        }
        Helper &operator[](int Cindex)
        {
            _CIndex = Cindex;
            return *this;
        }
    };

    Helper operator[](int RIndex)
    {
        return Helper(this, RIndex);
    }

    friend ostream &operator<<(ostream &os, const SmartArray &par)
    {
        cout << "Array:: " << endl;
        for (size_t i = 0x00; i < ARR_LEN; i++) {
            for (size_t j = 0x00; j < ARR_LEN; j++)
            {
                printf ("%02d ", par._Arr[i][j]);
            }
            cout << endl;
        }
        cout << endl;
        return os;
    }
};
#endif

class SmartArray
{
    int _Arr[ARR_LEN][ARR_LEN];
public:
    SmartArray ()
    {
        int count = 0x00;
        for (size_t i = 0x00; i < ARR_LEN; i++) {
            for (size_t j = 0x00; j < ARR_LEN; j++)
            {
                _Arr[i][j] = count++;
            }
        }
    }
    class Helper
    {
        SmartArray *outptr;
        int _RIndex;
        int _CIndex;
    public:
        Helper(SmartArray *outptr, int Rindex, int Cindex=0): outptr(outptr), _RIndex(Rindex), _CIndex(Cindex) {}

        class Helper1 {
            Helper *helper_ptr;
            public:
            Helper1(Helper *helper_ptr): helper_ptr(helper_ptr){}

            Helper1 & operator=(int val)
            {
                cout << "writing ...." << endl;
                this->helper_ptr->outptr->_Arr[helper_ptr->_RIndex][helper_ptr->_CIndex]  = val;
                return *this;
            }
            operator int()
            {
                cout << "reading ...." << endl;
                return this->helper_ptr->outptr->_Arr[helper_ptr->_RIndex][helper_ptr->_CIndex];
            }
            Helper1 &operator= (Helper1 &ObjRef)   // if this not defined then compiler uses default operator= which is bitwise copy
            {
                cout << "writing/reading ...." << endl;
                this->helper_ptr->outptr->_Arr[helper_ptr->_RIndex][helper_ptr->_CIndex] = ObjRef.helper_ptr->outptr->_Arr[helper_ptr->_RIndex][helper_ptr->_CIndex];
                return *this;
            }
        };
        Helper1 operator[](int Cindex)
        {
            _CIndex = Cindex;
            return Helper1(this);
        }
    };

    Helper operator[](int RIndex)
    {
        return Helper(this, RIndex);
    }

    friend ostream &operator<<(ostream &os, const SmartArray &par)
    {
        cout << "Array:: " << endl;
        for (size_t i = 0x00; i < ARR_LEN; i++) {
            for (size_t j = 0x00; j < ARR_LEN; j++)
            {
                printf ("%02d ", par._Arr[i][j]);
            }
            cout << endl;
        }
        cout << endl;
        return os;
    }
};

int main ()
{
    SmartArray objArr;
    cout << objArr << endl;
    objArr[0][1] = 99;        //writing
    int val = objArr[0][1];    //reading
    cout << "Val:: " << val << endl;
    objArr[0][0] = objArr[0][1];  // read/write

    cout << objArr << endl;

    return 0;
}
