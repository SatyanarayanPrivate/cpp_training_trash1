#if 0

#include <iostream>
#include <string>
using namespace std;

// function template

template <typename T>

inline T const& Max (T const& a, T const& b) {
    return a < b ? b:a;
}

int main (void) {
    
    int i = 39;
    int j = 20;
    cout << "Max (i, j): " << Max (i, j) << endl;
    
    double f1 = 13.5;
    double f2 = 20.7;
    cout << "Max (f1, f2): " << Max (f1, f2) << endl;
    
    string s1 = "Hello";
    string s2 = "World";
    cout << "Max (s1, s2): " << Max (s1, s2) << endl;
    
    cout << endl << endl;
    return 0;
}


int main (void) {
       
    cout << endl << endl;
    return 0;
}
#endif

#if 1 
// template specialization
#include <iostream>
using namespace std;

template <class T>
inline T square(T x)
{
   T result;
   result = x * x;
   return result;
};

// template specialization
template <>
string square<string>(string ss)
{
   return (ss+ss);
};

main()
{
   int i = 2, ii;
   string ww("Aaa");

   ii = square<int>(i);
   cout << i << ": " << ii << endl;

    cout << square<string>(ww) << endl;
}
#endif