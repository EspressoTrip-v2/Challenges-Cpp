#include <iostream>
#include <vector>

using namespace std;

/*
 Write a general-purpose function that can add any number of
 elements to the end of a container that has a method push_back(T&& value).
 */


template<typename T>
vector<T> addElements(initializer_list<T> items)
{
    vector<T> vec;
    for (auto &i: items)
    {
        vec.push_back(i);
    }
    return vec;
}

template<typename N>
void display(N &container)
{
    cout << "[ ";
    for (auto &i: container)
    {
        cout << i << " ";
    }
    cout << "]" << endl;
}

template<typename C, typename... Args>
void pushBack(C &c, Args &&...args)
{
    (c.push_back(args), ...);
}

template<typename S>
int print(S item)
{
    cout << item << " ";
    return 1;
}
int main()
{
    int num{10};
    cout << (print(num), 2 * num) << endl;

//    auto vectorA = addElements({"Juan", "Leroy", "Brendon", "Jason"});
//    auto vectorB = addElements({1, 2, 3, 3, 7, 2, 8, 9, 0});
//    display(vectorA);
//    display(vectorB);
//
//    vector<int> v;
//    pushBack(v, 1, 2, 3, 4, 5, 6);
//    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    return 0;
}
