#include <iostream>
using namespace std;
namespace nm1 {
    
    class shape {
    protected:
        int width;
        int hight;
    public:
        shape (int wdt=0, int hgt=0): width(wdt), hight(hgt) {
            cout <<"\nBase class constructor";
        }
        
        int getArea ()
        {
            cout << "\nBase Class area";
        }
    };
    
    class rectanlge: public shape {
    public: 
        rectanlge(int wdt=0, int hgt=0):shape(wdt,hgt) {
            cout <<"\nrectanlge class constructor";
        }
        int getArea ()
        {
            cout << "\nrectanlge Class area";
            return width * hight;
        }
    };
    class trianlge: public shape {
    public: 
        trianlge(int wdt=0, int hgt=0):shape(wdt,hgt) {
            cout <<"\ntrianlge class constructor";
        }
        int getArea ()
        {
            cout << "\ntrianlge Class area";
            return width * hight / 2;
        }
    };
}
namespace nm2 {
    
    class shape {
    protected:
        int width;
        int hight;
    public:
        shape (int wdt=0, int hgt=0): width(wdt), hight(hgt) {
            cout <<"\nBase class constructor";
        }
        
        virtual int getArea ()
        {
            cout << "\nBase Class area";
        }
    };
    
    class rectanlge: public shape {
    public: 
        rectanlge(int wdt=0, int hgt=0):shape(wdt,hgt) {
            cout <<"\nrectanlge class constructor";
        }
        int getArea ()
        {
            cout << "\nrectanlge Class area";
            return width * hight;
        }
    };
    class trianlge: public shape {
    public: 
        trianlge(int wdt=0, int hgt=0):shape(wdt,hgt) {
            cout <<"\ntrianlge class constructor";
        }
        int getArea ()
        {
            cout << "\ntrianlge Class area";
            return width * hight / 2;
        }
    };
}

int main (void) {
    {
//         using namespace nm1;
//         rectanlge obj (2, 3);
//         trianlge obj1(10, 20);
//         
//         cout << "\nReactangle Area:: " << obj.getArea() << " trianlge area:: " << obj1.getArea();
    }
    {
//         using namespace nm1;
//         shape *shape1;
//         rectanlge rect (2, 3);
//         trianlge tria(10, 20);
//         
//         shape1 = &rect;
//         rect.getArea();
//         shape1->getArea();
//         
//         shape1 = &tria;
//         tria.getArea();
//         shape1->getArea();       
    }
    {
        using namespace nm2;
        shape *shape1;
        shape shape2;
        rectanlge rect (2, 3);
        trianlge tria(10, 20);
        
        shape1 = &rect;
        rect.getArea();
        shape1->getArea();
        
        shape1 = &tria;
        tria.getArea();
        shape1->getArea();
        
        shape2.getArea();
    }
    
    cout << endl << endl;
    return 0;
}