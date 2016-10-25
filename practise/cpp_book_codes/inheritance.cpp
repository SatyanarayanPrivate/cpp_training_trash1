#include <iostream>
using namespace std;
namespace nm1 {
    
    class shape {
        int width;
        int hight;
    public:
        void setvalues (int usrwidth, int usrhight) {
            width = usrwidth;
            hight = usrhight;
        }
        int getwidth (void) {
            return width;
        }
        int gethight (void) {
            return hight;
        }
    };
    
    class rectanlge: public shape {
    public: 
        int getArea (void) {
            return getwidth() * gethight();
        }
    };
}

namespace nm2 {
    
    class shape {
    protected:
        int width;
        int hight;
    public:
        void setvalues (int usrwidth, int usrhight) {
            width = usrwidth;
            hight = usrhight;
        }
    };
   
    //class rectanlge: protected shape { // gives error for setvalues()
    class rectanlge: public shape {    
    public: 
        int getArea (void) {
            return width * hight;
        }
    };
}

namespace nm3 {
    
    class shape {
    protected:
        int width;
        int hight;
    public:
        void setvalues (int usrwidth, int usrhight) {
            width = usrwidth;
            hight = usrhight;
        }
    };
   
    class paintcost {
    public: 
        int getPrice (int area) {
            return area * 20;
        }
    };
    
    //class rectanlge: protected shape { // gives error for setvalues()
    class rectanlge: public shape, public paintcost {    
    public: 
        int getArea (void) {
            return width * hight;
        }
    };
}


int main (void) {
    {
        using namespace nm1;
        rectanlge obj1;
        
        obj1.setvalues (10, 20);
        
        cout << "\nArea:: " << obj1.getArea();
    }
    {
        using namespace nm2;
        rectanlge obj1;
        
//         obj1.width = 10; // we cannot access as its private of derived class
        obj1.setvalues (10, 20);
        
        cout << "\nArea:: " << obj1.getArea();
    }
    {
        using namespace nm3;
        rectanlge obj1;       
        obj1.setvalues (10, 20);        
        
        cout << "\nArea:: " << obj1.getArea() << " Price:: "<< obj1.getPrice (obj1.getArea());
    }
    
    
    cout << endl << endl;
    return 0;
}