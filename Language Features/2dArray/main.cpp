#include <iostream>
#include "array2d.h"
/*
 Write a class template that represents a two-dimensional array container with methods
 for element access (at() and data()), capacity querying, iterators,
 filling, and swapping. It should be possible to move objects of this type.
*/

using namespace std;
int main()
{
    array2d<int, 4, 5> ar({1, 2, 3, 100}, {11, 6, 7, 34, 16});
    array2d<string, 2, 2> stringArr({"Juan", "Leroy"}, {"Jason", "Steve"});

//    cout << stringArr;
//    cout << ar;

    cout << ar.at(1, 1);

    return 0;
}
