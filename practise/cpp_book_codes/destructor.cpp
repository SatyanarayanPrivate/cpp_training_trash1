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
        
        ~rectangle(void) {
            cout << "\nDestructor";
        }
        double calculate_area() ;
    };
}

int main (void) {
    {
        using namespace nm1;
        rectangle obj;       
    }
    cout << "\nend of program";
    cout << endl << endl;
    return 0;
}
