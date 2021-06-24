#include <iostream>
#include <algorithm>
#include <vector>
#include <any>


using namespace std;
/*
 Write a function template that can take any number of
 arguments and returns the minimum value of them all,
 using operator < for comparison. Write a variant
 of this function template that can be parameterized
 with a binary comparison function to use instead of operator <.
 */

template<typename T, typename... elements>
T minValue(T a, elements... args)
{
    T value{a};
    auto min = [&value](T el) mutable {
        if (value > el) value = el;
    };
    (min(args), ...);
    return value;
}


int main()
{
    cout << minValue(2, 5, 11, 3) << endl;
    cout << minValue(2, 0, 10, 3) << endl;

    return 0;
}
