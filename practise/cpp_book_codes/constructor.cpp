#include <iostream>
using namespace std;

namespace nm1 {
    class rectangle {
        double hight;
        double width;
    public:
        rectangle(void) {
            cout << "\nSimple Constructor";
        }
        
        rectangle(double hgt, double wdt){
            cout << "\nParameterized Constructor";
        }
        
        double calculate_area();
    };
}

namespace nm2 {
    class rectangle {
        double hight;
        double width;
    public:
        rectangle(double hgt, double wdt): hight (hgt), width (wdt) {
            cout << "\nInitialization Lists to Initialize Fields Constructor";
            cout << "\nhight:: " << hight << " width:: " << width;
        }
        
        double calculate_area();
    };
}

namespace nm3 {
    class rectangle {
        double hight;
        double width;
    public:
        rectangle(double hgt, double wdt): hight (hgt), width (wdt) {
            cout << "\nInitialization Lists to Initialize Fields Constructor";
            cout << "\nhight:: " << hight << " width:: " << width;
        }
        
        rectangle(const rectangle &obj)
        {
            cout << "\nCopy Constructor";
            cout << "\nhight:: " << obj.hight << " width:: " << obj.width;
            
            // garbage contents
            cout << "\nhight:: " << hight << " width:: " << width;
        }
        
        double calculate_area();
    };

}


int main (void) {
//     {
//         using namespace nm1;
//         rectangle obj;        
//         rectangle obj1(12.4, 11.4);
//     }
//     {
//         using namespace nm2;
//         rectangle obj2(12.4, 11.4);
//     }
    
    {
        using namespace nm3;
        rectangle obj(1.2, 3.4);
        rectangle obj1 (obj); // rectangle obj1 = obj;
    }
    
    cout << endl << endl;
    return 0;
}
