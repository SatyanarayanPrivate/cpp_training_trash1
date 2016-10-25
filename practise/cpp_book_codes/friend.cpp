#include <iostream>
using namespace std;

namespace nm1 {
    class rectangle {
        double hight;
        double width;
//         friend void print_data(rectangle obj); // this is also working
    public:
        rectangle(void): hight(10), width (20) {
            cout << "\nSimple Constructor";
        }
        
        ~rectangle(void) {
            cout << "\nDestructor";
        }
        double calculate_area() ;
        friend void print_data(rectangle obj);
    };

    void print_data (rectangle obj) {
        cout << "\nHight:: " << obj.hight << " width:: " << obj.width;
    }
}



int main (void) {
    {
        using namespace nm1;
        rectangle obj;       
        print_data (obj);
    }
    cout << "\nend of program";
    cout << endl << endl;
    return 0;
}
