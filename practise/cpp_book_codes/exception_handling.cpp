#include <iostream>
#include <exception>
using namespace std;

namespace nm1 {
    double division (int a, int b) {
        if (b == 0) {
            throw "Division by zero condition!";
        }
        return (a/b);
    }
}
namespace nm2 {
    
//     struct NewException: public exception {
//         const char *what () const throw () {
//             return "C++ NewException";
//         }
//     };
        
    // ==OR==
    class NewException: public exception {
    public:
        const char *what () const throw () {
            return "C++ NewException";
        }
    };
}
int main (void) {
    
#if 0
    { 
        using namespace nm1;
        int x = 50;
        int y = 0;
        double z = 0;

        try {
            z = division(x, y);
            cout << z << endl;
        }catch (const char* msg) {
            cerr << msg << endl;
        }
    }
#endif

    {
       using namespace nm2;
       try {
           throw NewException();
       }catch (NewException &e) {
            cout << "\nNewException cought:: " << e.what();
       }catch(std::exception& e) {
            //Other errors
        }
    }
    cout << endl << endl;
    return 0;
}
