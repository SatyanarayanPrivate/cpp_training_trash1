#include <iostream>
using namespace std;

namespace nm1 {
    void func1 () {
        cout << __func__ << endl;
    }
}

namespace nm1 {
    void func2 () {
        cout << __func__ << endl;
    }
}

namespace nm2 {
    void func1 () {
        cout << "nm2:: " << __func__ << endl;
    }    
    namespace nm3 {
        void func1 () {
            cout << "nm3:: "<< __func__ << endl;
        }    
    }
}

int main (void) {

#if 0
    using namespace nm1;
    
    func2();
#endif
    nm2::func1();

    using namespace nm2:: nm3;
    func1();

    cout << endl << endl;
    return 0;

}