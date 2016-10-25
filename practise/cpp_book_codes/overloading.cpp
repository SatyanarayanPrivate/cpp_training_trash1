#include <iostream>
using namespace std;

namespace nm1 {
    class rectangle {
        double d_hight;
        double d_width;
        int i_hight;
        int i_width;
    public:
        rectangle(double width, double hight): d_width(width), d_hight(hight) {
            cout << "\ndouble Constructor";
        }

        rectangle(int width, int hight): i_width(width), i_hight(hight) {
            cout << "\nint Constructor";
        }
        
        ~rectangle(void) {
            cout << "\nDestructor";
        }
        
        double d_getArea (void){
            return d_width * d_hight;
        }
        
        int i_getArea (void) {
            return i_width * i_hight;
        }        
    };
}

int main (void) {
    {
        using namespace nm1;
        double wdt = 10.3, hgt = 2.1;        
        int i_wdt = 2, i_hgt = 3;
        
        rectangle obj (wdt, hgt);
        rectangle obj1 (i_wdt, i_hgt);
        
        cout << "int:: " << obj1.i_getArea() << " double:: " << obj.d_getArea();
    }
    cout << "\nend of program";
    cout << endl << endl;
    return 0;
}
