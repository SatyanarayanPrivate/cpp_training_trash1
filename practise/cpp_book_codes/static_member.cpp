#include <iostream>
using namespace std;

namespace nm1 {
    class rectangle {
        double hight;
        double width;
        //static int obj_count; //gives error
    public:
        static int obj_count;
        rectangle(void): hight(10), width (20) {
            cout << "\nSimple Constructor";
            obj_count ++;
            
        }
        
        ~rectangle(void) {
            cout << "\nDestructor";
            obj_count --;
        }
        double calculate_area() ;
        
        static int get_count(void) {
//             return hight;    // gives compiler error
            return obj_count;            
        }
    };

}
using namespace nm1;
int rectangle::obj_count = 0x00;

int main (void) {
    {
        using namespace nm1;
        rectangle obj;       
        cout << "\nTotal objcounts:: " << rectangle::obj_count << "   " << rectangle::get_count();
        
    }
    cout << "\nTotal objcounts:: " << rectangle::obj_count;
    cout << "\nend of program";
    cout << endl << endl;
    return 0;
}
